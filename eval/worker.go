// Copyright (c) 2026 dywoq - MIT License
// A part of https://github.com/dywoq/vacui

package eval

import "github.com/dywoq/vacui/ast"

// Context is an API interface for evaluator workers.
type Context interface {
	Filename() string
	GlobalNode() ast.Node
}

// Worker is a function which scans and evaluates the top-level node,
// using other sub-workers for child nodes.
//
// Returns workers.ErrNoMatch if the top-level node doesn't match worker.
type Worker func(c Context) error
