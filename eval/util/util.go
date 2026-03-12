// Copyright (c) 2026 dywoq - MIT License
// A part of https://github.com/dywoq/vacui

package util

import (
	"fmt"

	"github.com/dywoq/vacui/ast"
	"github.com/dywoq/vacui/eval"
	"github.com/dywoq/vacui/token"
)

// Current returns the current processing top-level node.
// Returns nil if the evaluator encountered EOF.
func Current(c eval.Context) ast.Node {
	if c.Eof() {
		return nil
	}
	return c.Nodes()[c.Pos()]
}

// Error formats the given message with automatically inserted location,
// and returns it.
func Error(c eval.Context, pos token.Pos, msg string) error {
	return fmt.Errorf("Eval error: %s (at %s:%d:%d)", msg, c.Filename(), pos.Line, pos.Col)
}

// Errorf is the same as Error, but it lets you format your own message.
func Errorf(c eval.Context, pos token.Pos, format string, v ...any) error {
	return Error(c, pos, fmt.Sprintf(format, v...))
}
