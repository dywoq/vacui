// Copyright (c) 2026 dywoq - MIT License
// A part of https://github.com/dywoq/vacui

package workers

import (
	"fmt"

	"github.com/dywoq/vacui/ast"
	"github.com/dywoq/vacui/parser"
	"github.com/dywoq/vacui/parser/util"
	"github.com/dywoq/vacui/token"
)

type W struct{}

func (w *W) Append(a parser.WorkerAppender) error {
	workers := []parser.Worker{
		w.Function,
	}
	for _, worker := range workers {
		if err := a.AppendWorker(worker); err != nil {
			return err
		}
	}
	return nil
}

func (w *W) Function(c parser.Context) (ast.Node, error) {
	fmt.Println("function")
	name, err := util.ExpectKind(c, token.KIND_IDENTIFIER)
	if err != nil {
		return nil, err
	}
	_, err = util.ExpectLit(c, "{")
	if err != nil {
		return nil, err
	}

	body := []ast.Instruction{}
	for {
		if c.Eof() {
			return nil, util.Errorf(c, "Unexpected EOF during parsing function")
		}
		cur := util.Current(c)
		if cur.Lit == "}" {
			break
		}
		instr, err := w.Instruction(c)
		if err != nil {
			return nil, err
		}
		body = append(body, instr.(ast.Instruction))
	}

	_, err = util.ExpectLit(c, "}")
	if err != nil {
		return nil, err
	}

	return ast.Function{
		Name: name.Lit,
		Body: body,
		Pos:  name.Pos,
	}, nil
}
func (w *W) Instruction(c parser.Context) (ast.Node, error) {
	name, err := util.ExpectKind(c, token.KIND_INSTRUCTION)
	if err != nil {
		return nil, err
	}

	args := []ast.Node{}
	for {
		if c.Eof() {
			break
		}
		cur := util.Current(c)

		// Terminate if we hit another instruction OR the end of the function block
		if cur.Kind == token.KIND_INSTRUCTION || cur.Lit == "}" {
			break
		}

		val, err := w.Value(c)
		if err != nil {
			return nil, err
		}
		args = append(args, val)
	}

	return ast.Instruction{
		Name: name.Lit,
		Args: args,
		Pos:  name.Pos,
	}, nil
}

func (w *W) Value(c parser.Context) (ast.Node, error) {
	fmt.Println("value")
	val, err := util.ExpectKinds(c, []token.Kind{token.KIND_DIGIT, token.KIND_STRING, token.KIND_REGISTRY})
	if err != nil {
		return nil, err
	}
	return ast.Value{
		Lit:  val.Lit,
		Kind: val.Kind,
		Pos:  val.Pos,
	}, nil
}
