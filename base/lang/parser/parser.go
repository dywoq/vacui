// Copyright 2026 dywoq
//
// This code is released under Apache License 2.0:
// - https://www.apache.org/licenses/LICENSE-2.0
//
// The repository:
// - https://github.com/dywoq/vacui

package parser

import (
	"errors"
	"sync"
	"sync/atomic"

	"github.com/dywoq/vacui/base/lang/ast"
	"github.com/dywoq/vacui/base/lang/debug"
	"github.com/dywoq/vacui/base/lang/token"
)

// Options allows you to customize Parser.
type Options struct {
	// Logger is a debug logger Parser uses in API implementation.
	// It can be nil to use no logging functionality.
	Logger debug.Logger
}

// Parser is responsible for parsing tokens,
// and turning them into AST nodes, using workers.
type Parser struct {
	Options *Options

	on       atomic.Bool
	tokens   []*token.Tok
	workers  []Worker
	mu       sync.Mutex
	pos      int
	filepath string
}

// Implements Api interface
type api struct {
	p *Parser
}

// New creates a new pointer to Parser, using given options.
func New(o *Options) *Parser {
	return &Parser{
		Options: o,
	}
}

// AppendWorker appends new worker to the parser.
// If the parser is currently on, the function returns an error.
func (p *Parser) AppendWorker(w Worker) error {
	p.mu.Lock()
	defer p.mu.Unlock()
	if p.on.Load() {
		return errors.New("parser: can't modify parser because it's on")
	}
	p.workers = append(p.workers, w)
	return nil
}

// DoTokens gets tokens, processing each of them to turn them into AST nodes.
// Returns an error if one of workers failed.
func (p *Parser) DoTokens(filepath string, tokens []*token.Tok) (*ast.Tree, error) {
	p.mu.Lock()
	defer p.mu.Unlock()

	p.on.Store(true)
	defer func() {
		p.on.Store(false)
	}()
	p.reset(filepath, tokens)

	tree := &ast.Tree{}
	api := &api{p}

	for !api.Eof() {
		for _, worker := range p.workers {
			old := p.pos
			res, node := worker(api)
			if res.Err != nil {
				return nil, res.Err
			}
			if !res.Matched {
				p.pos = old
				continue
			}
			tree.Nodes = append(tree.Nodes, node)
		}
	}

	return tree, nil
}

func (p *Parser) reset(filepath string, tokens []*token.Tok) {
	p.filepath = filepath
	p.pos = 0
	p.tokens = tokens
}

func (a *api) Eof() bool {
	return a.p.pos >= len(a.p.tokens)
}

func (a *api) Filepath() string {
	return a.p.filepath
}

func (a *api) Input() []*token.Tok {
	return a.p.tokens
}

func (a *api) Pos() int {
	return a.p.pos
}

func (a *api) Advance() {
	if a.Eof() {
		return
	}
	a.p.pos++
}

func (a *api) Current() *token.Tok {
	return a.p.tokens[a.p.pos]
}

func (a *api) Debugf(format string, v ...any) {
	logger := a.p.Options.Logger
	if logger != nil {
		logger.Debugf(format, v...)
	}
}

func (a *api) Debugln(v ...any) {
	logger := a.p.Options.Logger
	if logger != nil {
		logger.Debugln(v...)
	}
}

func (a *api) Debug(v ...any) {
	logger := a.p.Options.Logger
	if logger != nil {
		logger.Debug(v...)
	}
}
