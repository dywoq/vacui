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

import "github.com/dywoq/vacui/base/lang/engine/token"

type context struct {
	p *Parser
}

func (c *context) Debugf(format string, v ...any) {
	c.p.config.DebugTracer.Debugf(format, v...)
}

func (c *context) Debugln(v ...any) {
	c.p.config.DebugTracer.Debugln(v...)
}

func (c *context) Debug(v ...any) {
	c.p.config.DebugTracer.Debug(v...)
}

func (c *context) Errorf(format string, v ...any) error {
	return c.p.config.ErrorsMaker.Errorf(format, v)
}

func (c *context) Error(msg string) error {
	return c.p.config.ErrorsMaker.Error(msg)
}

func (c *context) Eof() bool {
	return c.p.pos >= len(c.p.tokens)
}

func (c *context) Current() *token.Token {
	if c.Eof() {
		return nil
	}
	return c.p.tokens[c.p.pos]
}

func (c *context) Advance() {
	if c.Eof() {
		return
	}
	c.p.pos++
}

func (c *context) Filename() string {
	return c.p.config.Filename
}
