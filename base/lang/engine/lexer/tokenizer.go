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

package lexer

import (
	"github.com/dywoq/vacui/base/lang/engine/debug"
	"github.com/dywoq/vacui/base/lang/engine/errors"
	"github.com/dywoq/vacui/base/lang/engine/scan"
	"github.com/dywoq/vacui/base/lang/engine/token"
)

// Context represents a API for tokenizers to transform input
// into tokens.
type Context interface {
	debug.Tracer
	scan.Advancer
	scan.Backwards
	scan.Slicer
	scan.EofChecker
	scan.SofChecker
	errors.Maker
	Current() rune
	Position() *token.Position
}

// Tokenizer represents the function that tokenizes one or multiple
// characters, turning it into the token.
//
// Returns true if the token satisfies tokenizer requirements.
// Otherwise, you should try other available left tokenizers
// in the loop.
//
// Before checking if the tokenizer is satisfied, you should check
// if the error is not nil.
type Tokenizer func(c Context) (*token.Token, bool, error)
