// Copyright (c) 2026 dywoq - MIT License
// A part of https://github.com/dywoq/vacui

package util

import (
	"fmt"
	"slices"

	"github.com/dywoq/vacui/parser"
	"github.com/dywoq/vacui/token"
)

// Current returns the current token being processed.
// Returns nil if the parser encountered EOF (End Of File).
func Current(c parser.Context) *token.T {
	if c.Eof() {
		return nil
	}
	return c.Tokens()[c.Pos()]
}

// Error makes an error, automatically inserting the location
// and message.
func Error(c parser.Context, msg string) error {
	return fmt.Errorf("Parser error: %s (at %s:%d:%d)", msg, c.Filename(), Current(c).Pos.Line, Current(c).Pos.Col)
}

// Errorf is the same as Error, but it lets you format your own message.
func Errorf(c parser.Context, format string, v ...any) error {
	return Error(c, fmt.Sprintf(format, v...))
}

// ExpectLit checks if the current token literal matches lit.
// If it does, the function returns token and advances automatically,
// otherwise, it returns an error.
func ExpectLit(c parser.Context, lit string) (*token.T, error) {
	t := Current(c)
	if t.Lit == lit {
		c.Advance()
		return t, nil
	}
	return nil, Errorf(c, "Expected \"%s\" literal", lit)
}

// ExpectKind checks if the current token literal matches kind.
// If it does, the function returns token and advances automatically,
// otherwise, it returns an error.
func ExpectKind(c parser.Context, kind token.Kind) (*token.T, error) {
	t := Current(c)
	if t.Kind == kind {
		c.Advance()
		return t, nil
	}
	return nil, Errorf(c, "Expected \"%s\" token kind", kind)
}

// ExpectKinds iterates over kinds, checking if token matches any of them.
// The first match returns the token and automatically advances.
//
// Returns an error if it failed.
func ExpectKinds(c parser.Context, kinds []token.Kind) (*token.T, error) {
	t := Current(c)
	if slices.Contains(kinds, t.Kind) {
		c.Advance()
		return t, nil
	}
	return nil, Errorf(c, "Expected \"%v\" token kinds", kinds)
}
