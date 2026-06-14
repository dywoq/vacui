// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package config

import (
	"errors"
	"fmt"
	"io"
	"strings"
	"sync"
	"sync/atomic"
)

type Parser struct {
	on          atomic.Bool
	mu          sync.Mutex
	fileContent []rune
}

var (
	ErrParserOn         = errors.New("config parser is on")
	ErrFileContentEmpty = errors.New("given file content is empty")
)

func NewParser() *Parser {
	return &Parser{}
}

func (p *Parser) Read(r io.Reader) error {
	if p.on.Load() {
		return ErrParserOn
	}
	p.mu.Lock()
	defer p.mu.Unlock()
	content, err := io.ReadAll(r)
	if err != nil {
		return err
	}
	p.fileContent = []rune(string(content))
	return nil
}

func (p *Parser) expandVariableReferences(value string, m map[string]string) (string, error) {
	if len(value) == 0 {
		return value, nil
	}
	var b strings.Builder
	idx := 0
	for !(idx >= len(value)) {
		r := rune(value[idx])
		if r != '$' {
			idx++
			b.WriteRune(r)
			continue
		}
		idx += 2
		keyNameStart := idx
		for !(idx >= len(value)) && rune(value[idx]) != ')' {
			idx++
		}
		keyNameEnd := idx
		keyName := value[keyNameStart:keyNameEnd]
		if _, ok := m[keyName]; !ok {
			return "", fmt.Errorf("cannot find key %q", keyName)
		}
		keyValue := m[keyName]
		b.WriteString(keyValue)
		idx++
	}
	return b.String(), nil
}

func (p *Parser) Parse() (map[string]string, error) {
	p.mu.Lock()
	defer p.mu.Unlock()

	if len(p.fileContent) == 0 {
		return nil, ErrFileContentEmpty
	}

	var keyValue strings.Builder
	m := map[string]string{}
	lineNumber := 1

	for line := range strings.SplitSeq(string(p.fileContent), "\n") {
		if len(line) == 0 {
			lineNumber++
			continue
		}

		if hashPos := strings.Index(line, "#"); hashPos != -1 {
			lineNumber++
			continue
		}
		
		equalPos := strings.Index(line, "=")
		if equalPos != -1 {
			key := strings.Trim(line[0:equalPos], " \n\t")
			keyValue.WriteString(strings.Trim(line[equalPos+1:], " \n\t"))

			expandedValue, err := p.expandVariableReferences(keyValue.String(), m)
			if err != nil {
				return nil, err
			}
			keyValue.Reset()
			keyValue.WriteString(expandedValue)

			m[key] = keyValue.String()

			keyValue.Reset()
			lineNumber++

			continue
		}
	
		return nil, fmt.Errorf("cannot parse the %d line:\n%d | %s", lineNumber, lineNumber, line)
	}

	return m, nil
}
