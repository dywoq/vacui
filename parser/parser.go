// Copyright (c) 2026 dywoq - MIT License
// A part of https://github.com/dywoq/vacui

package parser

import (
	"errors"
	"sync"
	"sync/atomic"

	"github.com/dywoq/vacui/ast"
	"github.com/dywoq/vacui/scanner"
	"github.com/dywoq/vacui/token"
	"github.com/dywoq/vacui/workers"
)

// Parser is responsible for turning a sequence of tokens
// into AST nodes.
type Parser struct {
	on       atomic.Bool
	mu       sync.Mutex
	workers  []Worker
	filename string
	tokens   []*token.T
	pos      int
}

type api struct {
	p *Parser
}

// New returns a new pointer to Scanner.
func New() *Parser {
	p := &Parser{}
	p.on.Store(false)
	p.mu = sync.Mutex{}
	p.workers = []Worker{}
	p.tokens = []*token.T{}
	p.pos = 0
	return p
}

// ErrOn indicates the parser is currently working,
// and you can't apply any modifications to its settings.
var ErrOn = errors.New("parser is on")

// ErrTokensEmpty means there's no given tokens,
// therefore parser cannot continue.
var ErrTokensEmpty = errors.New("tokens empty ")

func (a *api) Filename() string   { return a.p.filename }
func (a *api) Eof() bool          { return a.p.pos > len(a.p.tokens) }
func (a *api) Pos() int           { return a.p.pos }
func (a *api) Tokens() []*token.T { return a.p.tokens }

func (a *api) Advance() {
	if a.Eof() {
		return
	}
	a.p.pos++
}

// Update sets new given tokens.
// Returns an error if the parser is currently working.
func (p *Parser) Update(tokens []*token.T) error {
	p.mu.Lock()
	defer p.mu.Unlock()
	if p.on.Load() {
		return ErrOn
	}
	p.tokens = tokens
	return nil
}

// Parse scans the tokens, parsing and turning them into AST nodes,
// using workers. Returns a sequence of global declarations.
//
// Returns an error if there are no workers, no tokens given,
// there's illegal token, or error from worker.
func (p *Parser) Parse(filename string) ([]ast.Node, error) {
	p.mu.Lock()
	defer p.mu.Unlock()

	p.on.Store(true)
	defer func() {
		p.on.Store(false)
	}()

	if len(p.workers) == 0 {
		return nil, workers.ErrNoWorkers
	}
	if len(p.tokens) == 0 {
		return nil, ErrTokensEmpty
	}

	p.filename = filename
	api := &api{}
	nodes := []ast.Node{}
	for !api.Eof() {
		n, err := p.perform(api)
		if err != nil {
			return nil, err
		}
		nodes = append(nodes, n)
	}
	return nodes, nil
}

func (p *Parser) perform(a *api) (ast.Node, error) {
	for _, w := range p.workers {
		old := p.pos
		n, err := w(a)
		if err != nil {
			if errors.Is(err, workers.ErrNoMatch) {
				p.pos = old
				continue
			}
			return nil, err
		}
		return n, nil
	}
	return nil, scanner.ErrIllegalToken
}
