// Copyright 2026 dywoq
//
// This code is released under Apache License 2.0:
// - https://www.apache.org/licenses/LICENSE-2.0
//
// The repository:
// - https://github.com/dywoq/vacui

package token

import "github.com/dywoq/vacui/base/lang/token"

const (
	Newline token.Kind = "newline"

	Identifier  token.Kind = "identifier"
	Instruction token.Kind = "instruction"
	Register    token.Kind = "register"
	Type        token.Kind = "type"

	Separator token.Kind = "separator"
)
