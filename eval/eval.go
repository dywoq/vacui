// Copyright (c) 2026 dywoq - MIT License
// A part of https://github.com/dywoq/vacui

package eval

import (
	"errors"
	"sync"
	"sync/atomic"

	"github.com/dywoq/vacui/ast"
	"github.com/dywoq/vacui/workers"
)

// Eval is what it performs instructions.
type Eval struct {
	on       atomic.Bool
	mu       sync.Mutex
	filename string
	workers  []Worker
	nodes    []ast.Node
	pos      int
}

type api struct {
	e *Eval
}

// ErrOn indicates the evaluator is on,
// therefore you can't modify its settings.
var ErrOn = errors.New("evaluator is on")

// ErrNoNodes reports there are no AST nodes
// appended to the evaluator.
var ErrNoNodes = errors.New("no nodes")

// ErrIllegalNode means the evaluator meet an illegal node.
var ErrIllegalNode = errors.New("illegal node")

// New returns a new pointer to Eval.
func New() *Eval {
	e := &Eval{}
	e.on.Store(false)
	e.mu = sync.Mutex{}
	e.filename = ""
	e.workers = []Worker{}
	e.nodes = []ast.Node{}
	return e
}

// Update updates the nodes.
// Returns an error if the evaluator is working.
func (e *Eval) Update(nodes []ast.Node) error {
	e.mu.Lock()
	defer e.mu.Unlock()
	if e.on.Load() {
		return ErrOn
	}
	e.nodes = nodes
	return nil
}

// AppendWorker appends new worker to the evaluator.
// Returns an error if the evaluator is working.
//
// Notice: You append only top-level evaluators. If you want to use
// other workers, place them in the same place where your top-level evaluators are,
// so they could be used.
func (e *Eval) AppendWorker(w Worker) error {
	e.mu.Lock()
	defer e.mu.Unlock()
	if e.on.Load() {
		return ErrOn
	}
	e.workers = append(e.workers, w)
	return nil
}

func (a *api) Filename() string  { return a.e.filename }
func (a *api) Pos() int          { return a.e.pos }
func (a *api) Nodes() []ast.Node { return a.e.nodes }
func (a *api) Eof() bool         { return a.e.pos >= len(a.e.nodes) }

// Do scans nodes and evaluates them, using the appended evaluators.
//
// Returns an error if there are no workers or no nodes appended,
// there's illegal node or one of workers failed.
func (e *Eval) Do(filename string) error {
	e.mu.Lock()
	defer e.mu.Unlock()

	if len(e.workers) == 0 {
		return workers.ErrNoWorkers
	}
	if len(e.nodes) == 0 {
		return ErrNoNodes
	}

	e.filename = filename
	api := &api{e}

	e.on.Store(true)
	defer func() {
		e.on.Store(false)
	}()

	for !api.Eof() {
		err := e.perform(api)
		if err != nil {
			return err
		}
	}

	return nil
}

func (e *Eval) perform(a *api) error {
	for _, w := range e.workers {
		old := e.pos
		err := w(a)
		if err != nil {
			if errors.Is(err, workers.ErrNoMatch) {
				e.pos = old
				continue
			}
			return err
		}
	}
	return ErrIllegalNode
}
