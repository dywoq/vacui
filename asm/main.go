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

package main

import (
	"encoding/json"
	"fmt"
	"os"

	"github.com/dywoq/vacui/asm/lexer"
	"github.com/dywoq/vacui/asm/lexer/tokenizer"
	"github.com/dywoq/vacui/asm/parser"
	"github.com/dywoq/vacui/asm/parser/mini"
)

func main() {
	f, err := os.Open("main.vasm")
	if err != nil {
		panic(err)
	}

	l, err := lexer.NewDebug(f, os.Stdout)
	if err != nil {
		panic(err)
	}

	d := tokenizer.Default{}
	d.Append(l)

	tokens, err := l.Do(f.Name())
	if err != nil {
		panic(err)
	}

	for _, token := range tokens {
		fmt.Printf("%v - %v\n", token.Literal, token.Kind)
	}

	p := parser.NewDebug(tokens, os.Stdout)
	pd := mini.Default{}
	pd.Append(p)

	tree, err := p.Do(f.Name())
	if err != nil {
		panic(err)
	}

	for _, topLevel := range tree.TopLevel {
		json, err := json.MarshalIndent(topLevel, "", "  ")
		if err != nil {
			panic(err)
		}
		fmt.Printf("json: %v\n", string(json))
	}
}
