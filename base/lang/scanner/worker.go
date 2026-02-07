// Copyright 2026 dywoq
//
// This code is released under Apache License 2.0:
// - https://www.apache.org/licenses/LICENSE-2.0
//
// The repository:
// - https://github.com/dywoq/vacui

package scanner

import (
	"github.com/dywoq/vacui/base/lang/token"
	"github.com/dywoq/vacui/base/lang/worker"
)

// Api represents the API workers use to transform input into the tokens.
type Api interface {
	// Eof reports whether the scanner has reached End Of File.
	Eof() bool

	// Sof reports whether the scanner has reached Start Of File.
	Sof() bool

	// Filename returns the name of file the scanner is currently processing.
	Filename() string

	// Input returns the user input the scanner is currently processing.
	Input() []rune

	// Pos returns the current token position.
	Pos() token.Pos
}

// Worker represents the scanner worker, which is responsible for turning
// input into the token.
type Worker func(api Api) (*worker.Result, *token.Tok)
