// Copyright (c) 2026 dywoq - MIT License
// A part of https://github.com/dywoq/vacui

package scanner

import (
	"github.com/dywoq/vacui/ast"
	"github.com/dywoq/vacui/token"
)

// Context represents an API for workers to interact with the parser.
type Context interface {
	Filename() string
	Eof() bool
	Pos() int
	Tokens() []*token.T
	Advance()
}

// WorkerAppender defines a method for appending new workers.
type WorkerAppender interface {
	AppendWorker(w Worker) error
}

// Worker represents the function, that works with the specific kind of token, and transforms it into Node.
// It helps to keep modular, and scalable architecture of the parser.
//
// Parser workers are appended for global declarations only. However, you can use sub-workers for statements,
// values etc.
//
// If the input doesn't satisfy the worker, it returns ErrNoMatch,
// which is a signal for the parser to try other worker.
type Worker func(c Context) (ast.Node, error)
