// Copyright 2026 dywoq
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package tokenizer

import (
	"slices"
	"unicode"

	"github.com/dywoq/vacui/asm/token"
)

// Default contains default language tokenizers.
type Default struct {
}

// Append appends all tokenizers into a.
func (d *Default) Append(a Appender) {
	a.AppendTokenizer(d.Identifier)
	a.AppendTokenizer(d.Number)
	a.AppendTokenizer(d.Separator)
	a.AppendTokenizer(d.String)
	a.AppendTokenizer(d.Char)
	a.AppendTokenizer(d.SpecialFunction)
}

func (d *Default) Identifier(c Context) (*token.Token, bool, error) {
	c.DebugPrintln("Identifier(): Met a possible identifier")

	cur := c.Current()
	if cur == 0 || !unicode.IsLetter(rune(cur)) && cur != '_' {
		c.DebugPrintln("Identifier(): No match")
		return nil, true, nil
	}

	start := c.Position().Position
	for {
		cur := c.Current()
		if cur == 0 || (!unicode.IsLetter(rune(cur)) && cur != '_' && !unicode.IsDigit(rune(cur))) {
			break
		}
		c.Advance()
	}

	end := c.Position().Position
	str, err := c.Slice(start, end)
	if err != nil {
		return nil, false, err
	}
	c.DebugPrintf("Identifier(): Got %v\n", str)

	if !token.IsIdentifier(str) {
		c.DebugPrintf("Identifier(): %v is not identifier\n", str)
		for range end - start {
			c.Backward()
		}
		return nil, true, err
	}

	c.DebugPrintf("Identifier(): %v is identifier\n", str)
	return token.New(str, token.Identifier, c.Position()), false, nil
}

func (d *Default) Number(c Context) (*token.Token, bool, error) {
	c.DebugPrintln("Number(): Met a possible number")

	cur := c.Current()
	if cur == 0 || !unicode.IsDigit(rune(cur)) {
		c.DebugPrintln("Number(): No match")
		return nil, true, nil
	}

	start := c.Position().Position
	for {
		cur := c.Current()
		if cur == 0 || !unicode.IsDigit(rune(cur)) {
			break
		}
		c.Advance()
	}
	end := c.Position().Position

	str, err := c.Slice(start, end)
	if err != nil {
		return nil, false, err
	}
	c.DebugPrintf("Number(): %v is number\n", str)
	return token.New(str, token.Number, c.Position()), false, nil
}

func (d *Default) Separator(c Context) (*token.Token, bool, error) {
	c.DebugPrintln("Separator(): Met a possible separator")
	cur := c.Current()
	if cur == 0 || !slices.Contains(token.Separators, string(cur)) {
		c.DebugPrintln("Separator(): No match")
		return nil, true, nil
	}
	c.DebugPrintf("Separator(): %v is separator\n", string(cur))
	c.Advance()
	return token.New(string(cur), token.Separator, c.Position()), false, nil
}

func (d *Default) String(c Context) (*token.Token, bool, error) {
	c.DebugPrintln("String(): Met a possible string")
	cur := c.Current()
	if cur == 0 || cur != '"' {
		c.DebugPrintln("String(): No match")
		return nil, true, nil
	}

	c.Advance() // consume opening quote
	start := c.Position().Position
	for {
		c.Advance()
		cur := c.Current()
		if c.Eof() {
			c.DebugPrintln("String(): Unexpected EOF")
			return nil, false, c.NewError("String(): Found EOF when tokenizing string, expected closing \"")
		}
		if cur == '"' {
			break
		}
	}
	end := c.Position().Position
	c.Advance() // consume closing quote
	str, err := c.Slice(start, end)
	if err != nil {
		return nil, false, err
	}
	c.DebugPrintf("String(): %v is a string\n", str)
	return token.New(str, token.String, c.Position()), false, nil
}

func (d *Default) Char(c Context) (*token.Token, bool, error) {
	c.DebugPrintln("Char(): Met a possible char")
	cur := c.Current()
	if cur == 0 || cur != '\'' {
		c.DebugPrintln("Char(): No match")
		return nil, true, nil
	}

	c.Advance()

	char := c.Current()
	if !unicode.IsLetter(rune(char)) {
		c.DebugPrintln("Char(): Expected letter")
		return nil, false, c.NewError("Char(): Expected letter")
	}

	c.Advance()

	if cur := c.Current(); cur != '\'' || c.Eof() {
		c.DebugPrintln("Char(): Unexpected EOF")
		return nil, false, c.NewError("Char(): Found EOF when tokenizing character, expected closing `")
	}

	c.Advance()

	return token.New(string(char), token.Char, c.Position()), false, nil
}

func (d *Default) SpecialFunction(c Context) (*token.Token, bool, error) {
	c.DebugPrintln("SpecialFunction(): Met a possible special function")
	cur := c.Current()
	if cur == 0 || !unicode.IsLetter(rune(cur)) {
		c.DebugPrintln("SpecialFunction(): No match")
		return nil, true, nil
	}

	start := c.Position().Position
	for {
		cur := c.Current()
		if c.Eof() || !unicode.IsLetter(rune(cur)) {
			break
		}
		c.Advance()
	}
	end := c.Position().Position

	str, err := c.Slice(start, end)
	if err != nil {
		return nil, false, err
	}

	if !slices.Contains(token.SpecialFunctions, str) {
		for range end - start {
			c.Backward()
		}
		c.DebugPrintf("SpecialFunction(): %v is not special function\n", str)
		return nil, true, nil
	}

	c.DebugPrintf("SpecialFunction(): %v is special function\n", str)
	return token.New(str, token.SpecialFunction, c.Position()), false, nil
}
