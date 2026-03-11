// Copyright (c) 2026 dywoq - MIT License
// A part of https://github.com/dywoq/vacui

package workers

import (
	"fmt"
	"slices"
	"unicode"

	"github.com/dywoq/vacui/scanner"
	"github.com/dywoq/vacui/scanner/util"
	"github.com/dywoq/vacui/token"
	"github.com/dywoq/vacui/workers"
)

type W struct{}

func (w *W) Append(c scanner.WorkerAppender) error {
	workers := []scanner.Worker{
		w.Instruction,
		w.Separator,
		w.Registry,
		w.Identifier,
		w.Digit,
		w.String,
	}
	for _, worker := range workers {
		if err := c.AppendWorker(worker); err != nil {
			return err
		}
	}
	return nil
}

func (w *W) Digit(c scanner.Context) (*token.T, error) {
	cur := util.Current(c)
	if !unicode.IsDigit(rune(cur)) {
		return nil, workers.ErrNoMatch
	}
	start := c.Pos().Index
	for {
		cur := util.Current(c)
		if c.Eof() || !unicode.IsDigit(rune(cur)) {
			break
		}
		c.Advance()
	}
	end := c.Pos().Index
	str, err := util.Slice(c, start, end)
	if err != nil {
		return nil, err
	}
	return token.New(str, token.KIND_DIGIT, c.Pos()), nil
}

func (w *W) Identifier(c scanner.Context) (*token.T, error) {
	cur := util.Current(c)
	if !unicode.IsLetter(rune(cur)) && rune(cur) != '_' {
		return nil, workers.ErrNoMatch
	}
	startPos := c.Pos()
	startIdx := startPos.Index
	for !c.Eof() {
		r := rune(util.Current(c))
		if !unicode.IsLetter(r) && !unicode.IsDigit(r) && r != '_' {
			break
		}
		c.Advance()
	}
	endIdx := c.Pos().Index
	str, err := util.Slice(c, startIdx, endIdx)
	if err != nil {
		return nil, err
	}
	if !token.IsIdentifier(str) {
		return nil, workers.ErrNoMatch
	}
	return token.New(str, token.KIND_IDENTIFIER, startPos), nil
}

func (w *W) Registry(c scanner.Context) (*token.T, error) {
	str, err := util.SelectWord(c)
	if err != nil {
		return nil, err
	}

	r := rune(util.Current(c))
	if !unicode.IsDigit(r) {
		return nil, workers.ErrNoMatch
	}

	total := fmt.Sprintf("%s%v", str, string(r))
	if !slices.Contains(token.Registries, total) {
		return nil, workers.ErrNoMatch
	}

	return token.New(total, token.KIND_REGISTRY, c.Pos()), nil
}

func (w *W) Separator(c scanner.Context) (*token.T, error) {
	cur := util.Current(c)
	str := string(cur)
	if !slices.Contains(token.Separators, str) {
		return nil,workers.ErrNoMatch
	}
	c.Advance()
	return token.New(str, token.KIND_SEPARATOR, c.Pos()), nil
}

func (w *W) String(c scanner.Context) (*token.T, error) {
	cur := util.Current(c)
	if rune(cur) != '"' {
		return nil, workers.ErrNoMatch
	}
	c.Advance()
	start := c.Pos().Index
	for {
		if c.Eof() {
			return nil, util.Errorf(c, "Unexpected EOF: No ending quote")
		}
		cur := util.Current(c)
		if cur == '"' {
			break
		}
		c.Advance()
	}
	end := c.Pos().Index
	c.Advance()
	str, err := util.Slice(c, start, end)
	if err != nil {
		return nil, err
	}
	return token.New(str, token.KIND_STRING, c.Pos()), nil
}

func (w *W) Instruction(c scanner.Context) (*token.T, error) {
	str, err := util.SelectWord(c)
	if err != nil {
		return nil, err
	}
	return token.New(str, token.KIND_INSTRUCTION, c.Pos()), nil
}
