// Copyright (c) 2026 dywoq - MIT License
// A part of https://github.com/dywoq/vacui

package scanner

import (
	"errors"
	"io"
	"sync"
	"sync/atomic"
	"unicode"

	"github.com/dywoq/vacui/token"
	"github.com/dywoq/vacui/workers"
)

// Scanner is responsible for turning code into a sequence of tokens, using workers.
// It's thread-safe and minimal.
type Scanner struct {
	on       atomic.Bool
	mu       sync.Mutex
	workers  []Worker
	filename string
	bytes    []byte
	pos      *token.Pos
}

type api struct {
	s *Scanner
}

// ErrOn indicates the scanner is currently working,
// and you can't apply any modifications to its settings.
var ErrOn = errors.New("scanner is on")

// ErrBytesEmpty means there's no given bytes,
// therefore scanner cannot continue.
var ErrBytesEmpty = errors.New("empty")

// ErrIllegalToken is returned when scanner
// met an illegal token.
var ErrIllegalToken = errors.New("illegal token")

// New returns a new pointer to Scanner.
func New() *Scanner {
	s := &Scanner{}
	s.on.Store(false)
	s.mu = sync.Mutex{}
	s.workers = []Worker{}
	s.bytes = []byte{}
	s.pos = &token.Pos{Line: 1, Col: 1, Index: 0}
	return s
}

func (a *api) Filename() string { return a.s.filename }
func (a *api) Eof() bool        { return a.s.pos.Index >= len(a.s.bytes) }
func (a *api) Pos() token.Pos   { return *a.s.pos }
func (a *api) Input() []byte    { return a.s.bytes }

func (a *api) Advance() {
	if a.Eof() {
		return
	}
	cur := a.s.bytes[a.s.pos.Index]
	if cur == '\n' {
		a.s.pos.Col = 1
		a.s.pos.Line++
	} else {
		a.s.pos.Col++
	}
	a.s.pos.Index++
}

// AppendWorker appends new worker to the Scanner.
// Returns ErrOn if the scanner is currently on.
func (s *Scanner) AppendWorker(w Worker) error {
	s.mu.Lock()
	defer s.mu.Unlock()
	if s.on.Load() {
		return ErrOn
	}
	s.workers = append(s.workers, w)
	return nil
}

// Update sets new bytes to the given ones.
// Returns an error if the scanner is currently active.
func (s *Scanner) Update(bytes []byte) error {
	s.mu.Lock()
	defer s.mu.Unlock()
	if s.on.Load() {
		return ErrOn
	}
	s.bytes = bytes
	return nil
}

// Update sets new bytes to the ones, received from r.
// Returns an error if the scanner is currently active,
// or it fails to read content from r.
func (s *Scanner) UpdateR(r io.Reader) error {
	s.mu.Lock()
	defer s.mu.Unlock()
	if s.on.Load() {
		return ErrOn
	}

	bytes, err := io.ReadAll(r)
	if err != nil {
		return err
	}

	s.bytes = bytes
	return nil
}

// Do scans the given bytes, turning them into a sequence of tokens
// and returning it. Sets the current filename.
//
// Returns an error if there are no workers, no bytes given,
// there's illegal token or error from worker.
//
// During processing token, it saves the current position.
// In case the worker didn't match, it reduces to the old position.
func (s *Scanner) Do(filename string) ([]*token.T, error) {
	s.mu.Lock()
	defer s.mu.Unlock()
	if len(s.workers) == 0 {
		return nil, workers.ErrNoWorkers
	}
	if len(s.bytes) == 0 {
		return nil, ErrBytesEmpty
	}
	s.filename = filename
	api := &api{s}
	tokens := []*token.T{}
	for !api.Eof() {
		s.skipWhitespace(api)
		t, err := s.perform(api)
		if err != nil {
			return nil, err
		}
		s.skipWhitespace(api)
		tokens = append(tokens, t)
	}
	return tokens, nil
}

func (s *Scanner) skipWhitespace(a *api) {
	for {
		if a.Eof() {
			break
		}
		cur := a.Input()[a.Pos().Index]
		if !unicode.IsSpace(rune(cur)) {
			break
		}
		a.Advance()
	}
}

func (s *Scanner) perform(api *api) (*token.T, error) {
	for _, w := range s.workers {
		old := *s.pos
		t, err := w(api)
		if err != nil {
			if errors.Is(err, workers.ErrNoMatch) {
				*s.pos = old
				continue
			}
			return nil, err
		}
		return t, nil
	}
	return nil, ErrIllegalToken
}
