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

package lexer

import (
	"fmt"
	"io"
	"log"
	"sync"
	"sync/atomic"
	"unicode"

	"github.com/dywoq/vacui/asm/pkg/lexer/tokenizer"
	"github.com/dywoq/vacui/asm/pkg/token"
)

type Lexer struct {
	// base
	r     io.Reader
	bytes []byte
	on    atomic.Bool

	// debug
	debugW      io.Writer
	debugOn     atomic.Bool
	debugLogger *log.Logger

	// tokenizers
	tokenizers []tokenizer.Tokenizer

	// mutex
	mu sync.Mutex

	// data
	filename string
	position *token.Position
}

// New creates a new instance of Lexer with debugging automatically turned off.
// The function tries to read bytes from r, and save it in Lexer.
//
// Returns an error if any failure is encountered.
func New(r io.Reader) (*Lexer, error) {
	l, err := newBase(r)
	if err != nil {
		return nil, err
	}
	l.debugOn.Store(false)
	l.debugW = nil
	return l, nil
}

// NewDebug creates a new instance of Lexer.
// It works the same as New, but the only difference is that NewDebug requires debug writer,
// and automatically turns debug mode on.
//
// Returns an error if any failure is encountered.
func NewDebug(r io.Reader, w io.Writer) (*Lexer, error) {
	l, err := newBase(r)
	if err != nil {
		return nil, err
	}
	l.debugOn.Store(true)
	l.debugW = w
	l.debugLogger = log.New(l.debugW, "", log.Default().Flags())
	return l, nil
}

func newBase(r io.Reader) (*Lexer, error) {
	l := &Lexer{}
	l.r = r
	bytes, err := io.ReadAll(r)
	if err != nil {
		return nil, err
	}
	l.bytes = bytes
	l.mu = sync.Mutex{}
	l.on.Store(false)
	l.position = &token.Position{Line: 1, Column: 1, Position: 0}
	return l, nil
}

// SetReader sets a new reader, which updates the underlying bytes.
//
// Panics if the lexer is currently working.
//
// Returns an error if reading fails.
func (l *Lexer) SetReader(r io.Reader) error {
	l.mu.Lock()
	defer l.mu.Unlock()
	if l.on.Load() {
		panic("lexer is on, can't set reader")
	}
	l.r = r
	bytes, err := io.ReadAll(r)
	if err != nil {
		return err
	}
	l.bytes = bytes
	return nil
}

// DebugSetWriter sets a new debugging writer.
// Panics if the lexer is currently working.
func (l *Lexer) DebugSetWriter(w io.Writer) {
	l.mu.Lock()
	defer l.mu.Unlock()
	if l.on.Load() {
		panic("lexer is on, can't set debug writer")
	}
	l.debugW = w
}

// DebugSetMode sets a debugging mode to b.
// Panics if the lexer is currently working.
func (l *Lexer) DebugSetMode(b bool) {
	if l.on.Load() {
		panic("lexer is on, can't set debug mode")
	}
	l.debugOn.Store(b)
}

// DebugOn returns true if debugging is on.
func (l *Lexer) DebugOn() bool {
	return l.debugOn.Load()
}

// AppendTokenizer appends a new tokenizer to the lexer.
// Panics if the lexer is currently working.
func (l *Lexer) AppendTokenizer(t tokenizer.Tokenizer) {
	l.mu.Lock()
	defer l.mu.Unlock()
	if l.on.Load() {
		panic("lexer is on, can't append tokenizer")
	}
	l.tokenizers = append(l.tokenizers, t)
}

// implements tokenizer.Context
type context struct {
	l *Lexer
}

func (c *context) Eof() bool {
	c.DebugPrintln("Eof(): Checking EOF (end of file)")
	return c.l.position.Position >= len(c.l.bytes)
}

func (c *context) Sof() bool {
	c.DebugPrintln("Sof(): Checking SOF (start of file)")
	return c.l.position.Position <= 0
}

func (c *context) Current() byte {
	if c.Eof() {
		return 0
	}
	b := c.l.bytes[c.l.position.Position]
	c.DebugPrintf("Current(): Getting current character: %v\n", string(b))
	return b
}

func (c *context) Advance() {
	c.DebugPrintln("Advance(): Advancing...")
	if c.Eof() {
		c.DebugPrintln("Advance(): Eof() is true, skipping")
		return
	}
	c.DebugPrintln("Advance(): Position++")
	c.l.position.Position++
	if cur := c.Current(); cur != 0 && cur == '\n' {
		c.DebugPrintln("Advance(): Met newline, increasing Line and resetting column to 1")
		c.l.position.Line++
		c.l.position.Column = 1
	} else {
		c.DebugPrintln("Advance(): Increasing Column")
		c.l.position.Column++
	}
}

func (c *context) Backward() {
	c.DebugPrintln("Backward(): Advancing backwards...")
	if c.Sof() {
		c.DebugPrintln("Backward(): Sof() is true, skipping")
		return
	}
	c.DebugPrintln("Backward(): Position--")
	c.l.position.Position--
	cur := c.Current()
	if cur == '\n' {
		c.DebugPrintln("Backward(): Met newline, decreasing Line and detecting column")
		c.l.position.Line--
		col := 1
		for i := c.l.position.Position - 1; i >= 0; i-- {
			if c.l.bytes[i] == '\n' {
				break
			}
			col++
		}
		c.DebugPrintln("Backward(): Detected column")
		c.l.position.Column = col
	} else {
		if c.l.position.Column > 1 {
			c.DebugPrintln("Backward(): Column--")
			c.l.position.Column--
		}
	}
}

func (c *context) Slice(start, end int) (string, error) {
	c.DebugPrintln("Slice(): Slicing...")
	switch {
	case start > end:
		c.DebugPrintln("Slice(): Failed slicing")
		return "", c.l.makeError(fmt.Sprintf("Start %v is higher than end %v", start, end))
	case start < 0:
		c.DebugPrintln("Slice(): Failed slicing")
		return "", c.l.makeError(fmt.Sprintf("Start %v is negative", start))
	case end > len(c.l.bytes):
		c.DebugPrintln("Slice(): Failed slicing")
		return "", c.l.makeError(fmt.Sprintf("End %v is out of bounds", end))
	}

	c.DebugPrintf("Slice(): Returning: [%v:%v]\n", start, end)
	return string(c.l.bytes[start:end]), nil
}

func (c *context) Position() *token.Position {
	c.DebugPrintf("Position(): Returning current position")
	return c.l.position
}

func (c *context) DebugPrintf(format string, a ...any) {
	if c.l.DebugOn() {
		c.l.debugLogger.Printf(format, a...)
	}
}

func (c *context) DebugPrint(a ...any) {
	if c.l.DebugOn() {
		c.l.debugLogger.Print(a...)
	}
}

func (c *context) DebugPrintln(a ...any) {
	if c.l.DebugOn() {
		c.l.debugLogger.Println(a...)
	}
}

func (c *context) NewError(str string) error {
	return c.l.makeError(str)
}

// Do starts lexer and runs tokenizers, printing debug messages
// if debug mode is on.
//
// Does nothing if there are no set tokenizers.
//
// Returns an error if tokenizer failed to transform
// input into a token.
func (l *Lexer) Do(filename string) ([]*token.Token, error) {
	c := &context{l}

	l.mu.Lock()
	defer l.mu.Unlock()

	l.reset(filename)

	c.DebugPrintln("Starting lexer...")
	l.on.Store(true)
	defer func() {
		c.DebugPrintln("Lexer ended")
		l.on.Store(false)
	}()

	if len(l.tokenizers) == 0 {
		c.DebugPrintln("No tokenizers detected")
		return nil, nil
	}

	tokens := []*token.Token{}
	for !c.Eof() {
		// We skip whitespace before and after tokenizing to avoid "Unknown character" error,
		// whose the source is double empty lines.
		l.skipComments(c)
		l.skipWhitespace(c)
		tok, err := l.tokenize(c)
		if err != nil {
			return nil, err
		}
		tokens = append(tokens, tok)
		l.skipWhitespace(c)
		l.skipComments(c)
	}
	return tokens, nil
}

func (l *Lexer) makeError(err string) error {
	return fmt.Errorf("%v (at %v:%v:%v)", err, l.filename, l.position.Line, l.position.Column)
}

func (l *Lexer) tokenize(c *context) (*token.Token, error) {
	for _, tokenizer := range l.tokenizers {
		c.DebugPrintln("Trying to tokenize...")
		tok, noMatch, err := tokenizer(c)
		if err != nil {
			c.DebugPrintln("Encountered an error when tokenizing")
			return nil, err
		}
		if noMatch {
			c.DebugPrintln("No match, trying other tokenizer...")
			continue
		}
		c.DebugPrintln("Successfully tokenized, returning token")
		return tok, err
	}
	return nil, l.makeError("Unknown character")
}

func (l *Lexer) skipWhitespace(c *context) {
	for cur := c.Current(); cur != 0 && unicode.IsSpace(rune(cur)); cur = c.Current() {
		c.Advance()
	}
}

func (l *Lexer) skipComments(c *context) {
	for {
		cur := c.Current()
		if cur != '#' {
			return
		}

		for cur != 0 && cur != '\n' {
			c.Advance()
			cur = c.Current()
		}

		if cur == '\n' {
			c.Advance()
		}

		if c.Eof() || c.Current() != '#' {
			return
		}
	}
}

func (l *Lexer) reset(filename string) {
	l.filename = filename
	l.position.Line = 1
	l.position.Column = 1
	l.position.Position = 0
}
