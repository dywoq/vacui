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

import "github.com/dywoq/vacui/base/lang/engine/token"

type context struct {
	l *Lexer
}

func (c *context) Debugf(format string, v ...any) {
	c.l.config.DebugTracer.Debugf(format, v...)
}

func (c *context) Debugln(v ...any) {
	c.l.config.DebugTracer.Debugln(v...)
}

func (c *context) Debug(v ...any) {
	c.l.config.DebugTracer.Debug(v...)
}

func (c *context) Errorf(format string, v ...any) error {
	return c.l.config.ErrorsMaker.Errorf(format, v)
}

func (c *context) Error(msg string) error {
	return c.l.config.ErrorsMaker.Error(msg)
}

func (c *context) Position() *token.Position {
	return c.l.pos
}

func (c *context) Eof() bool {
	return c.l.pos.Position >= len(c.l.runes)
}

func (c *context) Sof() bool {
	return c.l.pos.Position < len(c.l.runes)
}

func (c *context) Advance() {
	if c.Eof() {
		return
	}
	c.l.pos.Position++
	if r := c.l.runes[c.l.pos.Position]; r == '\n' {
		c.l.pos.Line++
		c.l.pos.Column = 1
	} else {
		c.l.pos.Column++
	}
}

func (c *context) Backwards() {
	if c.Sof() {
		return
	}
	c.l.pos.Position--
	cur := c.Current()
	if cur == '\n' {
		c.l.pos.Line--
		col := 1
		for i := c.l.pos.Position - 1; i >= 0; i-- {
			if c.l.runes[i] == '\n' {
				break
			}
			col++
		}
		c.l.pos.Column = col
	} else {
		if c.l.pos.Column > 1 {
			c.l.pos.Column--
		}
	}
}

func (c *context) Current() rune {
	if c.Eof() {
		return 0
	}
	return c.l.runes[c.l.pos.Position]
}

func (c *context) Slice(start, end int) (string, error) {
	if c.Eof() {
		return "", c.Error("reached EOF when slicing")
	}
	if start > end {
		return "", c.Error("start is higher than end")
	}
	if end > c.l.pos.Position {
		return "", c.Error("end is higher than the file length")
	}
	if start < 0 {
		return "", c.Error("start is negative")
	}
	return string(c.l.runes[start:end]), nil
}
