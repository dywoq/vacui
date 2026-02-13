// Copyright 2026 dywoq
//
// This code is released under Apache License 2.0:
// - https://www.apache.org/licenses/LICENSE-2.0
//
// The repository:
// - https://github.com/dywoq/vacui

// Package token defines token declarations, which is needed by the parser
// to build AST nodes.
//
// A sequence of tokens is built using scanner.
package token

// Kind identifies the token, letting the parser to recognize it.
type Kind string

// Pos stores the token position.
// It's needed for the error reporting.
type Pos struct {
	Line int
	Col  int
	Pos  int
}

// Tok represents the literal, containing its kind and position.
// It's received from the scanner from breaking the user code into tokens.
type Tok struct {
	Lit  string
	Kind Kind
	Pos  Pos
}
