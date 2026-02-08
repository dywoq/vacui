// Copyright 2026 dywoq
//
// This code is released under Apache License 2.0:
// - https://www.apache.org/licenses/LICENSE-2.0
//
// The repository:
// - https://github.com/dywoq/vacui

package parser

import (
	"github.com/dywoq/vacui/base/lang/ast"
	"github.com/dywoq/vacui/base/lang/debug"
	"github.com/dywoq/vacui/base/lang/token"
	"github.com/dywoq/vacui/base/lang/worker"
)

// Api represents the API workers use to transform tokens into AST nodes.
type Api interface {
	// Eof reports whether the parser has reached End Of File.
	Eof() bool

	// Filepath returns the path of file the parser is currently processing.
	Filepath() string

	// Input returns the tokens the parser is currently processing.
	Input() []*token.Tok

	// Pos returns the current parser position.
	Pos() int

	// Advance advances to the next position until the parser reached EOF.
	Advance()

	// Current returns the current token that's being processed.
	// Returns nil if it encountered EOF.
	Current() *token.Tok

	debug.Logger
}

// Worker represents the scanner worker, which is responsible for turning
// token into AST node.
//
// Workers, appended to the parser, are meant to be top-level only.
// Top-level workers use sub-workers to get AST nodes.
// Sub-workers are never appended to the parser.
type Worker func(api Api) (*worker.Result, ast.Node)

// WorkerAppender defines method for appending scanner workers.
type WorkerAppender interface {
	AppendWorker(w Worker) error
}
