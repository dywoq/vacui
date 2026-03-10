// Copyright (c) 2026 dywoq - MIT License
// A part of https://github.com/dywoq/vacui

// Package token represents a token definitions, which is crucial for parser to build AST nodes.
package token

import "unicode"

// Kind is used to identify tokens.
type Kind string

// T represents the literal in the source code
// with its kind and position.
type T struct {
	Lit  string `json:"identifier"`
	Kind Kind   `json:"kind"`
	Pos  Pos    `json:"pos"`
}

// Pos is a location of token in the code.
type Pos struct {
	Line  int `json:"line"`
	Col   int `json:"col"`
	Index int `json:"index"`
}

const (
	KIND_INSTRUCTION Kind = "instruction"
	KIND_DIGIT       Kind = "number"
	KIND_STRING      Kind = "string"
	KIND_SEPARATOR   Kind = "separator"
	KIND_REGISTER    Kind = "register"
	KIND_IDENTIFIER  Kind = "identifier"
)

// A set of literals for token kind.
var (
	Instructions = []string{
		"mov",
		"sys",
		"ret",
		"push",
		"pop",
	}

	Registers = []string{
		"x0",
		"x1",
		"x2",
		"x3",
		"x4",
		"x5",
		"x6",
		"x7",
	}

	Separators = []string{
		",",
		"[",
		"]",
		"{",
		"}",
	}
)

func New(lit string, kind Kind, pos Pos) *T {
	return &T{Lit: lit, Kind: kind, Pos: pos}
}

// IsIdentifier checks if str is a valid identifier.
// The rules:
//
//   - The length must fit into a range 0-255.
//   - The first rune of string must be not digit.
//   - The identifier must not contain any special symbols, except '_'.
//
// If any of these rules are violated, IsIdentifier returns false.
// Otherwise, it returns true.
func IsIdentifier(str string) bool {
    runes := []rune(str)
    l := len(runes)
    if l == 0 || l > 255 {
        return false
    }
    for i, r := range runes {
        if i == 0 && unicode.IsDigit(r) {
            return false
        }
        isLetter := unicode.IsLetter(r)
        isDigit := unicode.IsDigit(r)
        isUnderscore := (r == '_')
        if !isLetter && !isDigit && !isUnderscore {
            return false
        }
    }
    return true
}