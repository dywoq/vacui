// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

// Package worker defines the worker standard structs, which must be
// used in all worker function types.
//
// The worker is a modular small function, which works with X information
// and returns transformed, modified, or generated Y output. Its purpose 
// is to break complex scanning, parsing process into small, reusable units.
//
// This is an alternative to parse, tokenize god functions.
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
