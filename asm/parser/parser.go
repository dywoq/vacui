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

package parser

import (
	"fmt"
	"io"
	"log"
	"sync"
	"sync/atomic"

	"github.com/dywoq/vacui/asm/ast"
	"github.com/dywoq/vacui/asm/parser/mini"
	"github.com/dywoq/vacui/asm/token"
)

type Parser struct {
	// base
	tokens []*token.Token
	pos    int
	on     atomic.Bool

	// debug
	debugW      io.Writer
	debugOn     atomic.Bool
	debugLogger *log.Logger

	// mini parsers
	minis []mini.Parser

	// mutex
	mu sync.Mutex

	// data
	filename string
}

func New(tokens []*token.Token) *Parser {
	p := newBase(tokens)
	return p
}

func NewDebug(tokens []*token.Token, w io.Writer) *Parser {
	p := newBase(tokens)
	p.debugW = w
	p.debugOn.Store(true)
	p.debugLogger = log.New(p.debugW, "", log.Default().Flags())
	return p
}

func newBase(tokens []*token.Token) *Parser {
	p := &Parser{}
	p.on.Store(false)
	p.pos = 0
	p.tokens = tokens
	p.debugOn.Store(false)
	p.debugW = nil
	p.mu = sync.Mutex{}
	p.filename = ""
	return p
}

func (p *Parser) SetTokens(tokens []*token.Token) {
	p.mu.Lock()
	defer p.mu.Unlock()
	if p.on.Load() {
		panic("parser is on, can't set tokens")
	}
	p.tokens = tokens
}

// DebugSetWriter sets a new debugging writer.
// Panics if the parser is currently working.
func (p *Parser) DebugSetWriter(w io.Writer) {
	p.mu.Lock()
	defer p.mu.Unlock()
	if p.on.Load() {
		panic("parser is on, can't set debug writer")
	}
	p.debugW = w
	if p.debugLogger == nil {
		p.debugLogger = log.New(p.debugW, "", log.Default().Flags())
	}
}

// DebugSetMode sets a debugging mode to b.
// Panics if the parser is currently working.
func (p *Parser) DebugSetMode(b bool) {
	if p.on.Load() {
		panic("parser is on, can't set debug mode")
	}
	p.debugOn.Store(b)
}

// DebugOn returns true if debugging is on.
func (p *Parser) DebugOn() bool {
	return p.debugOn.Load()
}

// implements mini.Context
type context struct {
	p *Parser
}

func (c *context) IsEnd() bool {
	return c.p.pos >= len(c.p.tokens)
}

func (c *context) Current() *token.Token {
	if c.IsEnd() {
		return nil
	}
	return c.p.tokens[c.p.pos]
}

func (c *context) Advance() {
	if c.IsEnd() {
		return
	}
	c.p.pos++
}

func (c *context) Position() int {
	return c.p.pos
}

func (c *context) NewError(str string, pos token.Position) error {
	return c.p.makeError(str, pos)
}

func (c *context) ExpectLiteral(lit string) (*token.Token, bool) {
	tok := c.p.tokens[c.p.pos]
	if tok.Literal != lit {
		return nil, false
	}
	c.Advance()
	return tok, true
}

func (c *context) ExpectKind(kind token.Kind) (*token.Token, bool) {
	tok := c.p.tokens[c.p.pos]
	if tok.Kind != kind {
		return nil, false
	}
	c.Advance()
	return tok, true
}

func (c *context) DebugPrintf(format string, a ...any) {
	if c.p.DebugOn() {
		c.p.debugLogger.Printf(format, a...)
	}
}

func (c *context) DebugPrint(a ...any) {
	if c.p.DebugOn() {
		c.p.debugLogger.Print(a...)
	}
}

func (c *context) DebugPrintln(a ...any) {
	if c.p.DebugOn() {
		c.p.debugLogger.Println(a...)
	}
}

func (p *Parser) makeError(str string, pos token.Position) error {
	return fmt.Errorf("%v (%v:%v:%v)", str, p.filename, pos.Line, pos.Column)
}

func (p *Parser) Do(filename string) (*ast.Tree, error) {
	c := &context{p}

	p.mu.Lock()
	defer p.mu.Unlock()

	p.reset(filename)

	c.DebugPrintln("Starting parser...")
	p.on.Store(true)
	defer func() {
		p.on.Store(false)
		c.DebugPrintln("Parser ended")
	}()

	if len(p.minis) == 0 {
		c.DebugPrintln("No mini parsers detected")
		return &ast.Tree{TopLevel: []ast.Node{}}, nil
	}

	topLevel := []ast.Node{}
	for !c.IsEnd() {
		n, err := p.parse(c)
		if err != nil {
			return nil, err
		}
		topLevel = append(topLevel, n)
	}

	return &ast.Tree{
		TopLevel: topLevel,
	}, nil
}

func (p *Parser) AppendParser(m mini.Parser) {
	p.mu.Lock()
	defer p.mu.Unlock()
	if p.on.Load() {
		panic("parser is on, can't add new mini parsers")
	}
	p.minis = append(p.minis, m)
}

func (p *Parser) parse(c *context) (ast.Node, error) {
	// for getting position
	tok := p.tokens[p.pos]

	for _, parser := range p.minis {
		c.DebugPrintln("Trying to parse")
		got, noMatch, err := parser(c)
		if err != nil {
			c.DebugPrintln("Encountered an error when parsing")
			return nil, err
		}
		if noMatch {
			c.DebugPrintln("No match, trying other mini parser...")
			continue
		}
		c.DebugPrintln("Successfully parsed, returning node")
		return got, nil

	}
	return nil, p.makeError("Unknown token", tok.Position)
}

func (p *Parser) reset(filename string) {
	p.pos = 0
	p.filename = filename
}
