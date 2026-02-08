// Copyright 2026 dywoq
//
// This code is released under Apache License 2.0:
// - https://www.apache.org/licenses/LICENSE-2.0
//
// The repository:
// - https://github.com/dywoq/vacui

package ast

import "github.com/dywoq/vacui/base/lang/token"

// Node represents the element in AST tree.
type Node interface {
	Pos
	Node()
}

// Pos defines method for getting node position.
type Pos interface {
	Pos() token.Pos
}
