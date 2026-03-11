// Copyright (c) 2026 dywoq - MIT License
// A part of https://github.com/dywoq/vacui

package workers

import "errors"

// ErrNoMatch is a signal for the parser to try other worker,
// if the input didn't satisfy the previous scanner requirements.
var ErrNoMatch = errors.New("no match")

// ErrNoWorkers indicates that there are no workers appended.
var ErrNoWorkers = errors.New("no workers")
