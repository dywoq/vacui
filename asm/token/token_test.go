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

package token_test

import (
	"testing"

	"github.com/dywoq/vacui/asm/token"
)

func TestIsIdentifier(t *testing.T) {
	tests := []struct {
		input string
		want  bool
	}{
		// Valid
		{"__foo", true},
		{"foo_123", true},
		{"___", true},
		// Invalid
		{"##", false},
		{"1234", false},
	}

	// to prevent a lot of x and save readability, we append this test case manually.
	// these are invalid.
	str := []byte{}
	for range 256 {
		str = append(str, 'x')
	}
	tests = append(tests, struct {
		input string
		want  bool
	}{string(str), false})

	// same to types and separators, invalid.
	for _, sep := range token.Separators {
		tests = append(tests, struct {
			input string
			want  bool
		}{
			sep,
			false,
		})
	}
	for _, special := range token.SpecialFunctions {
		tests = append(tests, struct {
			input string
			want  bool
		}{
			special,
			false,
		})
	}

	for _, test := range tests {
		t.Run(test.input, func(t *testing.T) {
			got := token.IsIdentifier(test.input)
			if got != test.want {
				t.Errorf("got %v, want %v", got, test.want)
			}
		})
	}
}
