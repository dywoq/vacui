package mini

import (
	"fmt"
	"strconv"

	"github.com/dywoq/vacui/asm/ast"
	"github.com/dywoq/vacui/asm/token"
)

// Default contains default language parsers.
type Default struct {
}

func (d *Default) Append(a Appender) {
	a.AppendParser(d.TopLevel)
}

func (d *Default) TopLevel(c Context) (ast.Node, bool, error) {
	identifier, ok := c.ExpectKind(token.Identifier)
	if !ok {
		return nil, true, nil
	}
	expr, err := d.Expression(c)
	if err != nil {
		return nil, false, err
	}
	return &ast.TopLevel{Identifier: identifier.Literal, Expression: expr}, false, nil
}

func (d *Default) Expression(c Context) (ast.Node, error) {
	tok := c.Current()

	switch tok.Kind {
	case token.Number, token.Char, token.String:
		return d.Value(c)
	case token.Identifier:
		return d.ReferenceToIdentifier(c)
	case token.SpecialFunction:
		return d.SpecialFunction(c)
	}

	switch tok.Literal {
	case "(":
		return d.Function(c)
	}

	// Special case: Array
	if tok.Literal == "[" {
		return d.Array(c)
	}

	return nil, c.NewError("Unknown token", tok.Position)
}

func (d *Default) Value(c Context) (ast.Node, error) {
	expect := []token.Kind{
		token.Char,
		token.Number,
		token.String,
	}
	var lastTok *token.Token
	failed := true
	for _, expected := range expect {
		tok, ok := c.ExpectKind(expected)
		if !ok {
			lastTok = tok
			continue
		} else {
			failed = false
			lastTok = tok
			break
		}
	}
	if failed && lastTok != nil {
		return nil, c.NewError("Expected Char, Number or String", lastTok.Position)
	}
	return ast.Value{Literal: lastTok.Literal, Kind: lastTok.Kind}, nil
}

func (d *Default) Function(c Context) (ast.Node, error) {
	args, err := d.FunctionArgs(c)
	if err != nil {
		return nil, err
	}
	body, err := d.FunctionBody(c)
	if err != nil {
		return nil, err
	}
	return &ast.Function{
		Args: args,
		Body: body,
	}, nil
}

func (d *Default) FunctionBody(c Context) ([]ast.Instruction, error) {
	_, ok := c.ExpectLiteral("{")
	if !ok {
		return nil, c.NewError("Expected { when parsing function body", c.Current().Position)
	}

	instructions := []ast.Instruction{}
	for !c.IsEnd() {
		cur := c.Current()
		if cur.Literal == "}" {
			c.Advance()
			break
		}

		instrNode, err := d.Instruction(c)
		if err != nil {
			return nil, err
		}

		instr, ok := instrNode.(ast.Instruction)
		if !ok {
			return nil, c.NewError("Expected instruction", cur.Position)
		}

		instructions = append(instructions, instr)
	}

	return instructions, nil
}

func (d *Default) FunctionArgs(c Context) ([]ast.FunctionArgument, error) {
	_, ok := c.ExpectLiteral("(")
	if !ok {
		return nil, c.NewError("Expected '(' when parsing function arguments", c.Current().Position)
	}

	args := []ast.FunctionArgument{}
	for {
		cur := c.Current()
		if cur.Literal == ")" {
			c.Advance()
			break
		}

		name, ok := c.ExpectKind(token.Identifier)
		if !ok {
			return nil, c.NewError("Expected identifier when parsing function arguments", c.Current().Position)
		}

		variadic := false
		if c.Current().Literal == "^" {
			variadic = true
			c.Advance()
		}

		args = append(args, ast.FunctionArgument{Name: name.Literal, Variadic: variadic})

		cur = c.Current()
		if cur.Literal == "," {
			c.Advance()
			continue
		} else if cur.Literal == ")" {
			c.Advance()
			break
		} else {
			return nil, c.NewError("Expected ',' or ')' after argument", c.Current().Position)
		}
	}

	return args, nil
}

func (d *Default) ReferenceToIdentifier(c Context) (ast.Node, error) {
	identifier, ok := c.ExpectKind(token.Identifier)
	if !ok {
		return nil, c.NewError("Expected identifier", c.Current().Position)
	}
	return &ast.ReferenceToIdentifier{
		Identifier: identifier.Literal,
	}, nil
}

func (d *Default) Instruction(c Context) (ast.Node, error) {
	name, ok := c.ExpectKind(token.Identifier)
	if !ok {
		return nil, c.NewError("Expected name of the instruction", c.Current().Position)
	}

	args := []ast.Node{}
	for {
		cur := c.Current()
		if cur.Literal == ";" {
			c.Advance()
			break
		}

		expr, err := d.Expression(c)
		if err != nil {
			return nil, err
		}
		args = append(args, expr)

		cur = c.Current()
		if cur.Literal == "," {
			c.Advance()
			continue
		} else if cur.Literal == ";" {
			c.Advance()
			break
		} else {
			return nil, c.NewError("Expected ',' or ';' after instruction argument", cur.Position)
		}
	}

	return ast.Instruction{Name: name.Literal, Args: args}, nil
}

func (d *Default) Array(c Context) (ast.Node, error) {
	_, ok := c.ExpectLiteral("[")
	if !ok {
		return nil, c.NewError("Expected '[' in the start of array", c.Current().Position)
	}

	elements := []ast.Node{}
	for {
		cur := c.Current()
		if cur.Literal == "]" {
			c.Advance()
			break
		}

		expr, err := d.Expression(c)
		if err != nil {
			return nil, err
		}
		elements = append(elements, expr)

		cur = c.Current()
		if cur.Literal == "]" {
			c.Advance()
			break
		} else if cur.Literal == "," {
			c.Advance()
			continue
		} else {
			return nil, c.NewError("Expected ']' or ',' after array element", c.Current().Position)
		}
	}

	// Check for declaration of fixed size
	fixed := false
	fixedSize := 0
	cur := c.Current()
	if cur.Kind == token.Number {
		fixed = true
		num, err := strconv.Atoi(cur.Literal)
		if err != nil {
			return nil, c.NewError(fmt.Sprintf("Failed to convert literal into number: %v", err), cur.Position)
		}
		fixedSize = num
		c.Advance()
	}

	return ast.Array{Elements: elements, Fixed: fixed, FixedSize: fixedSize}, nil
}

func (d *Default) SpecialFunction(c Context) (ast.Node, error) {
	name, ok := c.ExpectKind(token.SpecialFunction)
	if !ok {
		return nil, c.NewError("Expected special function name", c.Current().Position)
	}

	_, ok = c.ExpectLiteral("(")
	if !ok {
		return nil, c.NewError("Expected opening '(' after special function name", c.Current().Position)
	}

	args := []ast.Node{}
	for {
		cur := c.Current()
		if cur.Literal == ")" {
			c.Advance()
			break
		}

		expr, err := d.Expression(c)
		if err != nil {
			return nil, err
		}
		args = append(args, expr)

		cur = c.Current()
		if cur.Literal == "," {
			c.Advance()
			continue
		} else if cur.Literal == ")" {
			c.Advance()
			break
		} else {
			return nil, c.NewError("Expected ',' or ';' after special function argument\n", c.Current().Position)
		}
	}

	return ast.SpecialFunction{Name: name.Literal, Args: args}, nil
}
