// Copyright 2026 dywoq
//
// This code is released under Apache License 2.0:
// - https://www.apache.org/licenses/LICENSE-2.0
//
// The repository:
// - https://github.com/dywoq/vacui

package scanner

import (
	"errors"
	"os"
	"sync"
	"sync/atomic"

	"github.com/dywoq/vacui/base/lang/debug"
	"github.com/dywoq/vacui/base/lang/token"
)

// Options allows you to customize Scanner.
type Options struct {
	// Logger is a debug logger Scanner uses in API implementation.
	// It can be nil to use no logging functionality.
	Logger debug.Logger
}

// Scanner is responsible for scanning input,
// and breaking it into a sequence of tokens, using workers.
type Scanner struct {
	Options *Options

	on       atomic.Bool
	input    []rune
	workers  []Worker
	mu       sync.Mutex
	pos      *token.Pos
	filepath string
}

// Implements Api interface
type api struct {
	s *Scanner
}

// New creates a new pointer to Scanner, using given options.
func New(options *Options) *Scanner {
	return &Scanner{
		Options: options,
		pos: &token.Pos{
			Line: 1,
			Col:  1,
			Pos:  0,
		},
	}
}

// AppendWorker appends new worker to the scanner.
// If the scanner is currently on, the function returns an error.
func (s *Scanner) AppendWorker(w Worker) error {
	s.mu.Lock()
	defer s.mu.Unlock()
	if s.on.Load() {
		return errors.New("scanner: can't modify scanner because it's on")
	}
	s.workers = append(s.workers, w)
	return nil
}

// DoFile gets file content in bytes, converting it to runes,
// and begins to transform it into a sequence of tokens.
//
// Returns an error if one of workers failed or the function failed to read file.
func (s *Scanner) DoFile(path string) ([]*token.Tok, error) {
	s.mu.Lock()
	defer s.mu.Unlock()

	s.on.Store(true)
	defer func() {
		s.on.Store(false)
	}()

	// Try to read file
	bytes, err := os.ReadFile(path)
	if err != nil {
		return nil, err
	}
	s.reset(path, []rune(string(bytes)))

	// Begin scanning
	api := &api{s}
	result := []*token.Tok{}
	for !api.Eof() {
		for _, worker := range s.workers {
			old := api.Pos()
			res, tok := worker(api)
			if res.Err != nil {
				return nil, res.Err
			}
			if res.Matched {
				*s.pos = old
				continue
			}
			result = append(result, tok)
			break
		}
	}
	return result, nil
}

func (s *Scanner) reset(filepath string, input []rune) {
	s.filepath = filepath
	s.pos = &token.Pos{
		Line: 1,
		Col:  1,
		Pos:  0,
	}
	s.input = input
}

func (a *api) Eof() bool {
	return a.s.pos.Pos >= len(a.s.input)
}

func (a *api) Filepath() string {
	return a.s.filepath
}

func (a *api) Input() []rune {
	return a.s.input
}

func (a *api) Pos() token.Pos {
	return *a.s.pos
}

func (a *api) Advance() {
	if a.Eof() {
		return
	}
	a.s.pos.Pos++
	if cur := a.Current(); cur != 0 && cur == '\n' {
		a.s.pos.Line++
		a.s.pos.Col = 1
	} else {
		a.s.pos.Col++
	}
}

func (a *api) Current() rune {
	if a.Eof() {
		return 0
	}
	return a.s.input[a.s.pos.Pos]
}

func (a *api) Debugf(format string, v ...any) {
	logger := a.s.Options.Logger
	if logger != nil {
		logger.Debugf(format, v...)
	}
}

func (a *api) Debugln(v ...any) {
	logger := a.s.Options.Logger
	if logger != nil {
		logger.Debugln(v...)
	}
}

func (a *api) Debug(v ...any) {
	logger := a.s.Options.Logger
	if logger != nil {
		logger.Debug(v...)
	}
}
