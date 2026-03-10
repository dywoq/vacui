// Copyright (c) 2026 dywoq - MIT License
// A part of https://github.com/dywoq/vacui

package util

import (
	"errors"
	"fmt"
	"unicode"

	"github.com/dywoq/vacui/scanner"
)

// Slice slices the code input from start to the end.
// Returns an error if start is higher than end, end is higher than file length
// or start is negative.
func Slice(c scanner.Context, start, end int) (string, error) {
	len := len(c.Input())
	switch {
	case start > end:
		return "", errors.New("start is higher than end")
	case end > len:
		return "", errors.New("end is higher than file length")
	case start < 0:
		return "", errors.New("start is negative")
	}
	return string(c.Input()[start:end]), nil
}

// Error automatically formats the error message,
// inserting error location and position.
func Error(c scanner.Context, msg string) error {
	return fmt.Errorf("Scanner error: %s (at %s:%d:%d)", msg, c.Filename(), c.Pos().Line, c.Pos().Col)
}

// Errorf is the same as Error, but it lets you format the message.
func Errorf(c scanner.Context, format string, v ...any) error {
	return Error(c, fmt.Sprintf(format, v...))
}

// Current returns the current processing byte.
// If there's EOF - the function returns 0 to avoid runtime panic.
func Current(c scanner.Context) byte {
	if c.Eof() {
		return 0
	}
	return c.Input()[c.Pos().Index]
}

// SelectWord automatically selects a word, which contains only with letters
// and returns it.
//
// If the first rune it meets is not letter, the function returns ErrNoMatch.
//
// Returns an error if it fails to slice input.
func SelectWord(c scanner.Context) (string, error) {
	cur := Current(c)
	if !unicode.IsLetter(rune(cur)) {
		return "", scanner.ErrNoMatch
	}
	start := c.Pos().Index
	for {
		cur := Current(c)
		if c.Eof() || !unicode.IsLetter(rune(cur)) {
			break
		}
		c.Advance()
	}
	end := c.Pos().Index
	str, err := Slice(c, start, end)
	if err != nil {
		return "", err
	}
	return str, nil
}
