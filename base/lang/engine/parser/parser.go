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
	"sync"
	"sync/atomic"

	"github.com/dywoq/vacui/base/lang/engine/ast"
	"github.com/dywoq/vacui/base/lang/engine/token"
)

type Parser struct {
	on     atomic.Bool
	config *Config

	pos    int
	tokens []*token.Token

	minis []Mini

	mu sync.Mutex
}

// New creates new Parser instance and returns it.
func New(c *Config) *Parser {
	p := &Parser{}
	p.on.Store(false)
	p.config = c
	p.pos = 0
	p.tokens = []*token.Token{}
	p.minis = []Mini{}
	return p
}

// LoadTokens loads new tokens, setting them internally.
// Panics if the parser is currently running.
func (p *Parser) LoadTokens(tokens []*token.Token) {
	p.mu.Lock()
	defer p.mu.Unlock()
	if p.on.Load() {
		panic("Can't modify parser during its work")
	}
	p.tokens = tokens
}

// Run parses tokens, turning them into nested nodes.
// Once it's finished, the function returns ast.Tree
// with nodes.
// 
// Returns an error if one of the mini parsers failed.
func (p *Parser) Run() (*ast.Tree, error) {
	p.mu.Lock()
	defer p.mu.Unlock()

	p.on.Store(true)
	defer func() {
		p.on.Store(false)
	}()

	nodes := []ast.Node{}
	tree := &ast.Tree{}

	c := &context{}

	for !c.Eof() {
		p, err := p.parse(c)
		if err != nil {
			return nil, err
		}
		nodes = append(nodes, p)
	}

	tree.Nodes = nodes
	return tree, nil
}

func (p *Parser) parse(c *context) (ast.Node, error) {
	for _, mini := range p.minis {
		n, match, err := mini(c)
		if err != nil {
			return nil, err
		}
		if !match {
			continue
		}
		return n, nil
	}
	return nil, c.Errorf("Unknown token: \"%s\"", c.Current().Literal)
}
