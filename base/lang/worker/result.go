// Copyright 2026 dywoq
//
// This code is released under Apache License 2.0:
// - https://www.apache.org/licenses/LICENSE-2.0
//
// The repository:
// - https://github.com/dywoq/vacui

package worker

// Result is the way to return a worker result.
type Result struct {
	// Matched reports whether the input matched
	// worker's requirements.
	Matched bool `json:"matched"`

	// Err represents the worker's error,
	// which is always checked first.
	Err error `json:"err"`
}

// Match returns a pointer to Result, setting Matched to true.
func Match() *Result {
	return &Result{Matched: true}
}

// Match returns a pointer to Result, setting Matched to false.
func NoMatch() *Result {
	return &Result{Matched: false}
}

// Err returns a pointer to Result, setting Err to provided error.
func Err(err error) *Result {
	return &Result{Err: err}
}
