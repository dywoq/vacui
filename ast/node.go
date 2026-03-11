// Copyright (c) 2026 dywoq - MIT License
// A part of https://github.com/dywoq/vacui

package ast

import "github.com/dywoq/vacui/token"

// Node represents the element in Abstract Syntax Tree,
// and specific a piece of code.
type Node interface {
	Node()
}

// Value is any value that's present in the code.
// It has its own string view and kind. Example:
//
//	// Digit (in code: 23)
//	Value { "23", token.KIND_DIGIT }
//
//	// String (in code: "Hi!")
//	Value { "Hi!", token.KIND_STRING }
type Value struct {
	Lit  string
	Kind token.Kind
}

// Instruction is a command to the interpreter to do something.
// It can be only inside function body. Example:
//
//		main {
//			# Return 0 (exit program)
//			ret 0;
//	    }
type Instruction struct {
	Name string
	Args []Node
}

// Function is a block in the code which does something.
// Its body contains only instructions. Example:
//
//	foo {
//		# Do something....
//		ret 0;
//	}
type Function struct {
	Name string
	Body []Node
}

func (Value) Node()       {}
func (Instruction) Node() {}
func (Function) Node()    {}
