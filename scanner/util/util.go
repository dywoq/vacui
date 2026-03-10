// Copyright (c) 2026 dywoq - MIT License
// A part of https://github.com/dywoq/vacui

package util

import (
	"errors"
	"fmt"

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
