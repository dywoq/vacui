// Copyright 2026 dywoq
//
// This code is released under Apache License 2.0:
// - https://www.apache.org/licenses/LICENSE-2.0
//
// The repository:
// - https://github.com/dywoq/vacui

// Package debug contains interfaces and helper functions to provide debugging
// in the scanners, parser and etc.
package debug

// Logger defines the methods, which is needed for debug logging.
//
// Users of this interface should not add prefixes or any formatting:
// the implementer handles all formatting.
//
// To see the exact formatting used, refer to the implementer documentation.
type Logger interface {
	Debugf(format string, v ...any)
	Debugln(v ...any)
	Debug(v ...any)
}
