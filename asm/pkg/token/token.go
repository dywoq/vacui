// Copyright 2026 dywoq
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package token

import (
	"slices"
	"unicode"
)

// Kind represents the token kind.
type Kind string

// Slice contains allowed literals of a specified token kind.
// To see if your literal is allowed, you can use:
//
//	 userLit := "bye"
//	 lits := token.Slice{"hi", "bye"}
//	 if !slices.Contains(lits, userLit) {
//			panic("no user literal found in lits")
//	 }
type Slice []string

// Positions represents the token position.
type Position struct {
	Line     int `json:"line"`
	Column   int `json:"column"`
	Position int `json:"position"`
}

// Token represents the literal in the code,
// which is used by parser to build AST tree.
type Token struct {
	Literal  string    `json:"literal"`
	Position *Position `json:"position"`
	Kind     Kind      `json:"kind"`
}

const (
	Identifier      Kind = "identifier"
	Number          Kind = "number"
	String          Kind = "string"
	Char            Kind = "char"
	Separator       Kind = "separator"
	SpecialFunction Kind = "special-function"
)

var (
	Separators = Slice{
		";",
		",",
		"[",
		"]",
		"{",
		"}",
		"(",
		")",
		"^",
	}

	SpecialFunctions = Slice{
		"at",
	}
)

func New(lit string, kind Kind, pos *Position) *Token {
	return &Token{lit, pos, kind}
}

// IsIdentifier checks whether str is a valid identifier:
//   - Must not start with digit;
//   - Must not contain any special symbols except _;
//   - Must not contain whitespaces;
//   - The length must be not longer than 255 or empty;
//   - Must not be reserved word or separator;
func IsIdentifier(str string) bool {
	if len(str) == 0 || len(str) > 255 {
		return false
	}

	if slices.Contains(Separators, str) || slices.Contains(SpecialFunctions, str) {
		return false
	}

	for idx, r := range str {
		if idx == 0 && unicode.IsDigit(r) {
			return false
		}
		if !unicode.IsLetter(r) && !unicode.IsDigit(r) && r != '_' {
			return false
		}
	}
	return true
}
