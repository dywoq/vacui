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
	"bytes"
	"strings"
	"testing"

	"github.com/dywoq/vacui/asm/pkg/lexer/tokenizer"
	"github.com/dywoq/vacui/asm/pkg/token"
)

func TestNew(t *testing.T) {
	input := "test input"
	l, err := New(strings.NewReader(input))
	if err != nil {
		t.Fatalf("New() error = %v", err)
	}
	if l == nil {
		t.Fatal("New() returned nil lexer")
	}
	if l.DebugOn() {
		t.Error("New() debug mode should be off")
	}
	if len(l.bytes) != len(input) {
		t.Errorf("New() bytes length = %v, want %v", len(l.bytes), len(input))
	}
}

func TestNewDebug(t *testing.T) {
	input := "test input"
	buf := &bytes.Buffer{}
	l, err := NewDebug(strings.NewReader(input), buf)
	if err != nil {
		t.Fatalf("NewDebug() error = %v", err)
	}
	if l == nil {
		t.Fatal("NewDebug() returned nil lexer")
	}
	if !l.DebugOn() {
		t.Error("NewDebug() debug mode should be on")
	}
	if l.debugW == nil {
		t.Error("NewDebug() debug writer should be set")
	}
}

func TestSetReader(t *testing.T) {
	l, err := New(strings.NewReader("initial"))
	if err != nil {
		t.Fatalf("New() error = %v", err)
	}

	newInput := "new input"
	err = l.SetReader(strings.NewReader(newInput))
	if err != nil {
		t.Fatalf("SetReader() error = %v", err)
	}

	if string(l.bytes) != newInput {
		t.Errorf("SetReader() bytes = %v, want %v", string(l.bytes), newInput)
	}

	l.on.Store(true)
	defer l.on.Store(false)
	defer func() {
		if r := recover(); r == nil {
			t.Error("SetReader() should panic when lexer is on")
		}
	}()
	l.SetReader(strings.NewReader("test"))
}

func TestDebugSetWriter(t *testing.T) {
	l, _ := New(strings.NewReader("test"))
	newWriter := &bytes.Buffer{}
	l.DebugSetWriter(newWriter)
	if l.debugW != newWriter {
		t.Error("DebugSetWriter() failed to set debug writer")
	}

	l.on.Store(true)
	defer l.on.Store(false)
	defer func() {
		if r := recover(); r == nil {
			t.Error("DebugSetWriter() should panic when lexer is on")
		}
	}()
	l.DebugSetWriter(newWriter)
}

func TestDebugSetMode(t *testing.T) {
	l, _ := New(strings.NewReader("test"))
	if l.DebugOn() {
		t.Error("DebugSetMode() initial state should be false")
	}

	l.DebugSetMode(true)
	if !l.DebugOn() {
		t.Error("DebugSetMode() failed to enable debug mode")
	}

	l.DebugSetMode(false)
	if l.DebugOn() {
		t.Error("DebugSetMode() failed to disable debug mode")
	}

	l.on.Store(true)
	defer l.on.Store(false)
	defer func() {
		if r := recover(); r == nil {
			t.Error("DebugSetMode() should panic when lexer is on")
		}
	}()
	l.DebugSetMode(true)
}

func TestAppendTokenizer(t *testing.T) {
	l, _ := New(strings.NewReader("test"))
	dummyTokenizer := func(c tokenizer.Context) (*token.Token, bool, error) {
		return nil, true, nil
	}

	l.AppendTokenizer(dummyTokenizer)
	if len(l.tokenizers) != 1 {
		t.Errorf("AppendTokenizer() tokenizers length = %v, want 1", len(l.tokenizers))
	}

	l.on.Store(true)
	defer l.on.Store(false)
	defer func() {
		if r := recover(); r == nil {
			t.Error("AppendTokenizer() should panic when lexer is on")
		}
	}()
	l.AppendTokenizer(dummyTokenizer)
}

func TestDoNoTokenizers(t *testing.T) {
	l, _ := New(strings.NewReader("test"))
	tokens, err := l.Do("test.asm")
	if err != nil {
		t.Fatalf("Do() error = %v", err)
	}
	if tokens != nil {
		t.Errorf("Do() tokens = %v, want nil", tokens)
	}
}

func TestDoWithTokenizers(t *testing.T) {
	l, _ := New(strings.NewReader("foo 123"))
	d := &tokenizer.Default{}
	d.Append(l)

	tokens, err := l.Do("test.asm")
	if err != nil {
		t.Fatalf("Do() error = %v", err)
	}

	if len(tokens) != 2 {
		t.Fatalf("Do() tokens length = %v, want 2", len(tokens))
	}

	if tokens[0].Literal != "foo" {
		t.Errorf("Do() first token literal = %v, want foo", tokens[0].Literal)
	}
	if tokens[0].Kind != token.Identifier {
		t.Errorf("Do() first token kind = %v, want identifier", tokens[0].Kind)
	}

	if tokens[1].Literal != "123" {
		t.Errorf("Do() second token literal = %v, want 123", tokens[1].Literal)
	}
	if tokens[1].Kind != token.Number {
		t.Errorf("Do() second token kind = %v, want number", tokens[1].Kind)
	}
}

func TestDoEmptyInput(t *testing.T) {
	l, _ := New(strings.NewReader(""))
	d := &tokenizer.Default{}
	d.Append(l)

	tokens, err := l.Do("test.asm")
	if err != nil {
		t.Fatalf("Do() error = %v", err)
	}
	if len(tokens) != 0 {
		t.Errorf("Do() tokens length = %v, want 0", len(tokens))
	}
}

func TestDoWhitespaceOnly(t *testing.T) {
	l, _ := New(strings.NewReader("   \t\n   "))
	d := &tokenizer.Default{}
	d.Append(l)

	tokens, err := l.Do("test.asm")
	if err == nil {
		t.Error("Do() should return error for whitespace-only input")
	}
	if tokens != nil && len(tokens) != 0 {
		t.Errorf("Do() tokens length = %v, want 0", len(tokens))
	}
}

func TestDoUnknownCharacter(t *testing.T) {
	l, _ := New(strings.NewReader("@"))
	d := &tokenizer.Default{}
	d.Append(l)

	_, err := l.Do("test.asm")
	if err == nil {
		t.Error("Do() should return error for unknown character")
	}
}

func TestContextEof(t *testing.T) {
	l, _ := New(strings.NewReader("test"))
	c := &context{l}

	if c.Eof() {
		t.Error("Eof() should be false at start")
	}

	l.position.Position = len(l.bytes)
	if !c.Eof() {
		t.Error("Eof() should be true at end")
	}
}

func TestContextSof(t *testing.T) {
	l, _ := New(strings.NewReader("test"))
	c := &context{l}

	if !c.Sof() {
		t.Error("Sof() should be true at start")
	}

	l.position.Position = 1
	if c.Sof() {
		t.Error("Sof() should be false after advancing")
	}
}

func TestContextCurrent(t *testing.T) {
	l, _ := New(strings.NewReader("test"))
	c := &context{l}

	if c.Current() != 't' {
		t.Errorf("Current() = %v, want 't'", c.Current())
	}

	l.position.Position = len(l.bytes)
	if c.Current() != 0 {
		t.Errorf("Current() at EOF = %v, want 0", c.Current())
	}
}

func TestContextAdvance(t *testing.T) {
	l, _ := New(strings.NewReader("t\nest"))
	c := &context{l}

	if l.position.Position != 0 || l.position.Line != 1 || l.position.Column != 1 {
		t.Error("Advance() initial position incorrect")
	}

	c.Advance()
	if l.position.Position != 1 {
		t.Errorf("Advance() position = %v, want 1", l.position.Position)
	}

	c.Advance()
	if l.position.Line != 2 {
		t.Errorf("Advance() line after newline = %v, want 2", l.position.Line)
	}
	if l.position.Column != 2 {
		t.Errorf("Advance() column after newline = %v, want 2", l.position.Column)
	}

	l.position.Position = len(l.bytes)
	c.Advance()
	if l.position.Position != len(l.bytes) {
		t.Error("Advance() should not advance at EOF")
	}
}

func TestContextBackward(t *testing.T) {
	l, _ := New(strings.NewReader("test"))
	c := &context{l}

	l.position.Position = 4
	c.Backward()
	if l.position.Position != 3 {
		t.Errorf("Backward() position = %v, want 3", l.position.Position)
	}

	l.position.Position = 0
	c.Backward()
	if l.position.Position != 0 {
		t.Error("Backward() should not go below 0")
	}
}

func TestContextSlice(t *testing.T) {
	l, _ := New(strings.NewReader("test"))
	c := &context{l}

	tests := []struct {
		name    string
		start   int
		end     int
		want    string
		wantErr bool
	}{
		{"valid slice", 0, 4, "test", false},
		{"partial slice", 1, 3, "es", false},
		{"start > end", 3, 1, "", true},
		{"negative start", -1, 2, "", true},
		{"out of bounds", 0, 10, "", true},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			got, err := c.Slice(tt.start, tt.end)
			if (err != nil) != tt.wantErr {
				t.Errorf("Slice() error = %v, wantErr %v", err, tt.wantErr)
				return
			}
			if got != tt.want {
				t.Errorf("Slice() = %v, want %v", got, tt.want)
			}
		})
	}
}

func TestContextPosition(t *testing.T) {
	l, _ := New(strings.NewReader("test"))
	c := &context{l}

	pos := c.Position()
	if pos.Line != 1 || pos.Column != 1 || pos.Position != 0 {
		t.Errorf("Position() = %+v, want {Line:1 Column:1 Position:0}", pos)
	}

	l.position.Line = 5
	l.position.Column = 10
	l.position.Position = 20
	pos = c.Position()
	if pos.Line != 5 || pos.Column != 10 || pos.Position != 20 {
		t.Errorf("Position() after update = %+v, want {Line:5 Column:10 Position:20}", pos)
	}
}

func TestDoMultipleTokenizers(t *testing.T) {
	input := `foo "bar" ` + "`" + `a` + "`" + ` 123 ; [ ] { }`
	l, _ := New(strings.NewReader(input))
	d := &tokenizer.Default{}
	d.Append(l)

	tokens, err := l.Do("test.asm")
	if err != nil {
		t.Fatalf("Do() error = %v", err)
	}

	expectedTokens := []struct {
		literal string
		kind    token.Kind
	}{
		{"foo", token.Identifier},
		{"bar", token.String},
		{"a", token.Char},
		{"123", token.Number},
		{";", token.Separator},
		{"[", token.Separator},
		{"]", token.Separator},
		{"{", token.Separator},
		{"}", token.Separator},
	}

	if len(tokens) != len(expectedTokens) {
		t.Fatalf("Do() tokens length = %v, want %v", len(tokens), len(expectedTokens))
	}

	for i, expected := range expectedTokens {
		if tokens[i].Literal != expected.literal {
			t.Errorf("Do() token[%v] literal = %v, want %v", i, tokens[i].Literal, expected.literal)
		}
		if tokens[i].Kind != expected.kind {
			t.Errorf("Do() token[%v] kind = %v, want %v", i, tokens[i].Kind, expected.kind)
		}
	}
}

func TestDoStringWithQuotes(t *testing.T) {
	input := `"hello world"`
	l, _ := New(strings.NewReader(input))
	d := &tokenizer.Default{}
	d.Append(l)

	tokens, err := l.Do("test.asm")
	if err != nil {
		t.Fatalf("Do() error = %v", err)
	}

	if len(tokens) != 1 {
		t.Fatalf("Do() tokens length = %v, want 1", len(tokens))
	}

	if tokens[0].Literal != "hello world" {
		t.Errorf("Do() string literal = %v, want 'hello world'", tokens[0].Literal)
	}

	if tokens[0].Kind != token.String {
		t.Errorf("Do() string kind = %v, want string", tokens[0].Kind)
	}
}

func TestDoUnterminatedString(t *testing.T) {
	input := `"unterminated`
	l, _ := New(strings.NewReader(input))
	d := &tokenizer.Default{}
	d.Append(l)

	_, err := l.Do("test.asm")
	if err == nil {
		t.Error("Do() should return error for unterminated string")
	}
}

func TestDoUnterminatedChar(t *testing.T) {
	input := "`a"
	l, _ := New(strings.NewReader(input))
	d := &tokenizer.Default{}
	d.Append(l)

	_, err := l.Do("test.asm")
	if err == nil {
		t.Error("Do() should return error for unterminated char")
	}
}

func TestDoCharWithNonLetter(t *testing.T) {
	input := "`1`"
	l, _ := New(strings.NewReader(input))
	d := &tokenizer.Default{}
	d.Append(l)

	_, err := l.Do("test.asm")
	if err == nil {
		t.Error("Do() should return error for char with non-letter")
	}
}

func TestDoLineNumberTracking(t *testing.T) {
	input := "foo\nbar\nbaz"
	l, _ := New(strings.NewReader(input))
	d := &tokenizer.Default{}
	d.Append(l)

	tokens, err := l.Do("test.asm")
	if err != nil {
		t.Fatalf("Do() error = %v", err)
	}

	if len(tokens) != 3 {
		t.Fatalf("Do() tokens length = %v, want 3", len(tokens))
	}

	if tokens[0].Literal != "foo" {
		t.Errorf("Do() token[0] literal = %v, want foo", tokens[0].Literal)
	}

	if tokens[1].Literal != "bar" {
		t.Errorf("Do() token[1] literal = %v, want bar", tokens[1].Literal)
	}

	if tokens[2].Literal != "baz" {
		t.Errorf("Do() token[2] literal = %v, want baz", tokens[2].Literal)
	}
}

func TestDoDebugOutput(t *testing.T) {
	input := "foo"
	buf := &bytes.Buffer{}
	l, err := NewDebug(strings.NewReader(input), buf)
	if err != nil {
		t.Fatalf("NewDebug() error = %v", err)
	}

	d := &tokenizer.Default{}
	d.Append(l)

	_, err = l.Do("test.asm")
	if err != nil {
		t.Fatalf("Do() error = %v", err)
	}

	if buf.Len() == 0 {
		t.Error("Do() debug output should not be empty")
	}
}
