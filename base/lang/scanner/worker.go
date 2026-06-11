// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package scanner

import (
	"github.com/dywoq/vacui/base/lang/token"
	"github.com/dywoq/vacui/base/lang/worker"
)

// Context is an API interface between scan workers and
// scanner that implements it.
type Context interface {
	FileName() string
	FileContent() []rune
	Advance()
	Idx() int
	Eof() bool
}

// Worker uses the given [Context] implementation to
// return token to scanner.
type Worker func(c Context) (*token.T, *worker.Result)

// WorkerAppender defines a method for appending workers.
type WorkerAppender interface {
	AppendWorker(w Worker) error
}
