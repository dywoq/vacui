package lexer

import (
	"github.com/dywoq/vacui/base/lang/engine/debug"
	"github.com/dywoq/vacui/base/lang/engine/errors"
	"github.com/dywoq/vacui/base/lang/engine/scan"
	"github.com/dywoq/vacui/base/lang/engine/token"
)

// Context represents a API for tokenizers to transform input
// into tokens.
type Context interface {
	debug.Tracer
	scan.Advancer
	scan.Backwards
	scan.Slicer
	errors.Maker
	Current() rune
	Position() token.Position
}

// Tokenizer represents the function that tokenizes one or multiple
// characters, turning it into the token.
//
// Returns true if the token satisfies tokenizer requirements.
// Otherwise, you should try other available left tokenizers
// in the loop.
//
// Before checking if the tokenizer is satisfied, you should check
// if the error is not nil.
type Tokenizer func(c Context) (*token.Token, bool, error)
