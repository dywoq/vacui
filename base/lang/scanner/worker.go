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
}

// Worker uses the given [Context] implementation to
// return token to scanner.
type Worker func(c Context) (*token.T, *worker.Result)
