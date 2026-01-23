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
