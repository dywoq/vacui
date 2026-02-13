// Copyright 2026 dywoq
//
// This code is released under Apache License 2.0:
// - https://www.apache.org/licenses/LICENSE-2.0
//
// The repository:
// - https://github.com/dywoq/vacui

package scanner

import "errors"

// Slice is a helper functions, which slices input around start and end.
//
// Returns an error if:
//   - start is lower than zero;
//   - start is higher than end;
//   - end is higher than the input.
func Slice(a Api, start, end int) (string, error) {
	input := a.Input()
	if start < 0 {
		return "", errors.New("slice: start is lower than zero")
	}
	if end < start {
		return "", errors.New("slice: start is higher than end")
	}
	if end > len(input) {
		return "", errors.New("slice: end is higher than input length")
	}
	return string(input[start:end]), nil
}
