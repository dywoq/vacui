// Copyright (c) 2026 dywoq - MIT License
// A part of https://github.com/dywoq/vacui

package scanner

import (
	"errors"

	"github.com/dywoq/vacui/token"
)

// Context represents an API for workers to interact with the scanner.
type Context interface {
	Filename() string
	Eof() bool
	Pos() token.Pos
	Input() []byte
	Advance()
}

// WorkerAppender defines a method for appending new workers.
type WorkerAppender interface {
	AppendWorker(w Worker) error
}

// Worker represents the function, that works with the input
// and specific kind of token. It helps to keep modular, and scalable
// architecture of the scanner.
//
// For example, we have:
//
//	func WorkerIdentifier(c Context) (*token.T, error) { ... }
//
// WorkerIdentifier is responsible only for one thing: scanning input and return identifier token.
//
// If the input doesn't satisfy the worker, it returns ErrNoMatch,
// which is a signal for the scanner to try other worker.
type Worker func(c Context) (*token.T, error)

// ErrNoMatch is a signal for the scanner to try other worker,
// if the input didn't satisfy the previous scanner requirements.
var ErrNoMatch = errors.New("no match")

// ErrNoWorkers indicates that there are no workers appended.
var ErrNoWorkers = errors.New("no workers")
