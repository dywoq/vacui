// Copyright 2026 dywoq
//
// This code is released under Apache License 2.0:
// - https://www.apache.org/licenses/LICENSE-2.0
//
// The repository:
// - https://github.com/dywoq/vacui

package scanner

import (
	"github.com/dywoq/vacui/base/lang/debug"
	"github.com/dywoq/vacui/base/lang/token"
	"github.com/dywoq/vacui/base/lang/worker"
)

// Api represents the API workers use to transform input into the tokens.
type Api interface {
	// Eof reports whether the scanner has reached End Of File.
	Eof() bool

	// Filepath returns the path of file the scanner is currently processing.
	Filepath() string

	// Input returns the user input the scanner is currently processing.
	Input() []rune

	// Pos returns the current token position.
	Pos() token.Pos

	// Advance advances to the next position until the scanner reached EOF.
	// Updates the line and column to 0 if it encountered new line.
	Advance()

	// Current returns the current rune that's being processed.
	// Returns 0 if the scanner encountered EOF.
	Current() rune

	debug.Logger
}

// Worker represents the scanner worker, which is responsible for turning
// input into the token.
//
// Scanner workers are tried in order, and the first match is added to the result
// in the scanner loop.
type Worker func(api Api) (*worker.Result, *token.Tok)

// WorkerAppender defines method for appending scanner workers.
type WorkerAppender interface {
	AppendWorker(w Worker) error
}
