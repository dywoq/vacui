// Copyright (c) 2026 dywoq - MIT License
// A part of https://github.com/dywoq/vacui

package workers

import (

	"unicode"

	"github.com/dywoq/vacui/scanner"
	"github.com/dywoq/vacui/scanner/util"
	"github.com/dywoq/vacui/token"
)

type W struct{}

func (w *W) Append(c scanner.WorkerAppender) error {
	workers := []scanner.Worker{
		w.Identifier,
		w.Digit,
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
		return nil, scanner.ErrNoMatch
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
        return nil, scanner.ErrNoMatch
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
        return nil, scanner.ErrNoMatch
    }
    return token.New(str, token.KIND_IDENTIFIER, startPos), nil
}