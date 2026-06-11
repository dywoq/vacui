// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package scanner

import (
	"errors"
	"sync"
	"sync/atomic"

	"github.com/dywoq/vacui/base/lang/token"
	"github.com/dywoq/vacui/base/lang/worker"
)

// S is responsible for scanning file content and
// transforming it into a sequence of tokens.
type S struct {
	on          atomic.Bool
	mu          sync.Mutex
	workers     []Worker
	filename    string
	filecontent []rune
}

type context struct {
	idx int
	s   *S
}

var (
	ErrOn               = errors.New("scanner is on")
	ErrFileContentEmpty = errors.New("file content is empty")
)

func New(filename string) *S {
	return &S{filename: filename}
}

// SetFileContent sets the file content to the underlying rune slice.
// Returns [ErrOn] if scanner is currently on.
func (s *S) SetFileContent(content []rune) error {
	if s.on.Load() {
		return ErrOn
	}
	s.mu.Lock()
	defer s.mu.Unlock()
	s.filecontent = content
	return nil
}

// AppendWorker appends new scan worker to the underlying slice.
// Returns [ErrOn] if scanner is currently on.
func (s *S) AppendWorker(w Worker) error {
	if s.on.Load() {
		return ErrOn
	}
	s.mu.Lock()
	defer s.mu.Unlock()
	s.workers = append(s.workers, w)
	return nil
}

// Scan scans the given file content and returns a sequence of tokens,
// gathered from scan workers.
//
// Returns [ErrFileContentEmpty] if file content slice length is 0.
//
// Returns [worker.ErrNoWorkers] if there are no scan workers appended.
//
// Returns any error from scan workers.
func (s *S) Scan() ([]*token.T, error) {
	s.mu.Lock()
	defer s.mu.Unlock()

	if len(s.filecontent) == 0 {
		return nil, ErrFileContentEmpty
	}

	if len(s.workers) == 0 {
		return nil, worker.ErrNoWorkers
	}

	tokens := []*token.T{}
	context := &context{0, s}

	for !context.Eof() {
		for _, w := range s.workers {
			tok, res := w(context)
			if res.State&worker.StateNoMatch != 0 {
				continue
			}
			if res.State&worker.StateErr != 0 {
				return nil, res.Err
			}
			if res.State&worker.StateOk != 0 {
				tokens = append(tokens, tok)
			}
		}
	}

	return tokens, nil
}

func (c *context) FileName() string {
	return c.s.filename
}

func (c *context) FileContent() []rune {
	return c.s.filecontent
}

func (c *context) Advance() {
	if c.Eof() {
		return
	}
	c.idx++
}

func (c *context) Idx() int {
	return c.idx
}

func (c *context) Eof() bool {
	return c.idx >= len(c.s.filecontent)
}
