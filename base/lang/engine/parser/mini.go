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

package parser

import (
	"github.com/dywoq/vacui/base/lang/engine/ast"
	"github.com/dywoq/vacui/base/lang/engine/scan"
)

type Context interface {
	scan.Advancer
	scan.EofChecker
}

// Mini represents the function that parses top level declarations,
// using other mini parsers to parse expressions, statements etc.
//
// Returns true if the token matched. Otherwise, it returns false,
// which means parser will try next mini parser.
//
// You should check error first before checking, if it matched.
type Mini func(c Context) (ast.Node, bool, error)

// MiniAppender defines method for appending mini parsers.
type MiniAppender interface {
	AppendMini(m Mini)
}
