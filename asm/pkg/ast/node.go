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

package ast

import "github.com/dywoq/vacui/asm/pkg/token"

type Node interface {
	Node()
}

type TopLevel struct {
	Identifier string `json:"identifier"`
	Expression Node   `json:"expression"`
}

type Value struct {
	Literal string     `json:"literal"`
	Kind    token.Kind `json:"kind"`
}

type ReferenceToIdentifier struct {
	Identifier string `json:"identifier"`
}

type Function struct {
	Args []FunctionArgument `json:"args"`
	Body []Instruction      `json:"body"`
}

type FunctionArgument struct {
	Name     string `json:"name"`
	Variadic bool   `json:"variadic"`
}

type Instruction struct {
	Name string `json:"name"`
	Args []Node `json:"args"`
}

type Array struct {
	Elements  []Node `json:"elements"`
	Fixed     bool   `json:"fixed"`
	FixedSize int    `json:"fixed_size"`
}

type IndexAccess struct {
	Expression Node `json:"expression"`
	Index      int  `json:"index"`
}

type SpecialFunction struct {
	Name string `json:"name"`
	Args []Node `json:"args"`
}

func (TopLevel) Node()              {}
func (Value) Node()                 {}
func (Function) Node()              {}
func (FunctionArgument) Node()      {}
func (Instruction) Node()           {}
func (ReferenceToIdentifier) Node() {}
func (Array) Node()                 {}
func (IndexAccess) Node()           {}
func (SpecialFunction) Node()       {}
