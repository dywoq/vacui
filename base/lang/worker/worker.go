// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

// Package worker defines worker types, which must be
// used in all worker function types.
//
// Worker processes input and returns output along with its result.
// This is an alternative to big complex functions with nested
// parsing/scanning logic.
package worker

type State uint64

type Result struct {
	Err   error
	State State
}

var (
	StateOk  State = 1 << 0
	StateErr State = 1 << 1
)

func Ok() *Result {
	return &Result{Err: nil, State: StateOk}
}

func Err(err error) *Result {
	return &Result{Err: err, State: StateErr}
}
