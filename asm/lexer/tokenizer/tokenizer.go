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

package tokenizer

import (
	"github.com/dywoq/vacui/asm/debug"
	"github.com/dywoq/vacui/asm/token"
)

type Context interface {
	// Eof checks if lexer encountered end of file.
	Eof() bool

	// Sof checks if lexer encountered start of file.
	Sof() bool

	// Advance advances to the next position in the file.
	// Updates line if it encountered new line (\n).
	// Notice that it doesn't advance when lexer encounters end of file.
	Advance()

	// Backwards advances to the next position backwards.
	// It doesn't do anything if it encountered start of file.
	Backward()

	// Current returns the current processing byte of the file.
	// Returns 0 if lexer encountered end of file.
	Current() byte

	// Slice slices the input within start and end, returning string.
	// Returns error if:
	// 	- start is higher than end;
	//  - start is negative;
	//  - end is out of bounds.
	Slice(start, end int) (string, error)

	// Position returns the current position in the file.
	Position() token.Position

	// NewError creates a new error, which automatically has location of the error.
	NewError(str string) error

	debug.Context
}

// Tokenizer represents function that transforms input
// into a token. Each tokenizer always has only one responsibility
// of tokenizing something, forming modular design.
//
// Returns true if input doesn't match the requirements of tokenizer,
// and lexer tries to use other tokenizer.
type Tokenizer func(c Context) (*token.Token, bool, error)

// Appender defines an interface for appending tokenizers.
type Appender interface {
	AppendTokenizer(t Tokenizer)
}
