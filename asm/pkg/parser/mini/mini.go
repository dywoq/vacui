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

package mini

import (
	"github.com/dywoq/vacui/asm/pkg/ast"
	"github.com/dywoq/vacui/asm/pkg/debug"
	"github.com/dywoq/vacui/asm/pkg/token"
)

type Context interface {
	// IsEnd reports whether the parser has reached the end.
	IsEnd() bool

	// Current returns the current token.
	// If the parser reached the end, the function returns nil.
	Current() *token.Token

	// Advance advances to the next token.
	// If the parser reached the end, the function returns.
	Advance()

	// Position returns the current position.
	Position() int

	// NewError makes a new error with automatically inserted token position
	// and parser position.
	NewError(str string, pos *token.Position) error

	// ExpectLiteral expects a literal from the current token.
	// If the token literal doesn't satisfy lit, the function returns false,
	// otherwise, it returns true.
	//
	// The function automatically advances when returns true.
	ExpectLiteral(lit string) (*token.Token, bool)

	// ExpectKind expects a kind from the current token.
	// If the token kind doesn't satisfy kind, the function returns false,
	// otherwise, it returns true.
	//
	// The function automatically advances when returns true.
	ExpectKind(kind token.Kind) (*token.Token, bool)

	debug.Context
}

// Parser parses tokens into AST tree node.
// Each mini parser has only one responsibility for parsing something.
//
// Returns true if token doesn't match mini parser requirements.
type Parser func(c Context) (ast.Node, bool, error)

// Appended defines an interface for appending mini parsers.
type Appender interface {
	AppendParser(p Parser)
}
