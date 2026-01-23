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
	"io"
	"sync"
	"sync/atomic"

	"github.com/dywoq/vacui/base/lang/engine/token"
)

type Lexer struct {
	on atomic.Bool

	config     *Config
	tokenizers []Tokenizer

	pos   *token.Position
	runes []rune

	mu sync.Mutex
}

// New returns the new instance of Lexer,
// with configuration c.
func New(c *Config) *Lexer {
	l := &Lexer{}
	l.on.Store(false)
	l.config = c
	l.tokenizers = []Tokenizer{}
	l.pos = &token.Position{Line: 1, Column: 1}
	l.runes = []rune{}
	l.mu = sync.Mutex{}
	return l
}

// Read reads bytes from r and converts them to runes,
// saving it internally,
//
// Panics if the lexer is currently running.
//
// Returns an error if it fails to read bytes from r.
func (l *Lexer) Read(r io.Reader) error {
	l.mu.Lock()
	defer l.mu.Unlock()
	if l.on.Load() {
		panic("Unable to modify lexer during its work")
	}
	runes, err := io.ReadAll(r)
	l.runes = []rune(string(runes))
	return err
}

// Config returns the configuration of the lexer.
func (l *Lexer) Config() *Config {
	l.mu.Lock()
	defer l.mu.Unlock()
	return l.config
}

// AppendTokenizer appends new tokenizer to the lexer.
// Panics if the lexer is currently running.
func (l *Lexer) AppendTokenizer(t Tokenizer) {
	l.mu.Lock()
	defer l.mu.Unlock()
	if l.on.Load() {
		panic("Unable to modify lexer during its work")
	}
	l.tokenizers = append(l.tokenizers, t)
}

// Run runs tokenizers in the loop to transform
// input into a sequence of tokens.
//
// Returns (nil, nil) if there are no tokenizers and input is empty.
//
// Returns an error if one of tokenizers failed.
func (l *Lexer) Run() ([]*token.Token, error) {
	l.mu.Lock()
	defer l.mu.Unlock()
	
	l.on.Store(true)
	defer func(){
		l.on.Store(false)
	}()

	if len(l.tokenizers) == 0 {
		return nil, nil
	}
	if len(l.runes) == 0 {
		return nil, nil
	}

	tokens := []*token.Token{}
	c := &context{l}

	for !c.Eof() {
		tok, err := l.tokenize(c)
		if err != nil {
			return nil, err
		}

		tokens = append(tokens, tok)
	}

	return tokens, nil
}

func (l *Lexer) tokenize(c *context) (*token.Token, error) {
	for _, tokenizer := range l.tokenizers {
		tok, match, err := tokenizer(c)
		if err != nil {
			return nil, err
		}
		if !match {
			continue
		}
		return tok, nil
	}
	return nil, c.Errorf("Unknown character: %v", c.Current())
}
