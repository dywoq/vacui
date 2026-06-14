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

// Parser is responsible for parsing configuration files
// and giving map of parsed keys.
type Parser struct {
	on      atomic.Bool
	mu      sync.Mutex
	content []rune
}

var (
	ErrParserOn         = errors.New("config parser is on")
	ErrFileContentEmpty = errors.New("given file content is empty")
)

func NewParser() *Parser {
	return &Parser{}
}

// Read reads the content from r and writes it
// to the underlying slice.
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
	p.content = []rune(string(content))
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

func (p *Parser) isMultiline(value string) bool {
	return strings.HasSuffix(value, "\\")
}

func (p *Parser) cutOffSlash(value string) string {
	res, _ := strings.CutSuffix(value, "\\")
	return res
}

func (p *Parser) trim(s string) string {
	return strings.Trim(s, " \n\t")
}

// Parse parses the given content, returning the map of config keys
// and values.
func (p *Parser) Parse() (map[string]string, error) {
	p.mu.Lock()
	defer p.mu.Unlock()

	if len(p.content) == 0 {
		return nil, ErrFileContentEmpty
	}

	var keyValue strings.Builder
	m := map[string]string{}
	isParsingMultiline := false
	isConfigKey := false
	currentKey := ""
	lineNumber := 1

	for line := range strings.SplitSeq(string(p.content), "\n") {
		if hashPos := strings.Index(line, "#"); hashPos != -1 || len(line) == 0 {
			lineNumber++
			continue
		}

		if isParsingMultiline {
			trimmedLine := p.trim(line)
			isParsingMultiline = p.isMultiline(trimmedLine)

			if isParsingMultiline {
				keyValue.WriteString(p.cutOffSlash(trimmedLine))
				lineNumber++
				continue
			}

			keyValue.WriteString(trimmedLine)

			if isConfigKey {
				expandedValue, err := p.expandVariableReferences(keyValue.String(), m)
				if err != nil {
					return nil, err
				}
				m[currentKey] = expandedValue
				keyValue.Reset()
				isConfigKey = false
			}

			lineNumber++
			continue
		}

		equalPos := strings.Index(line, "=")
		if equalPos != -1 {
			isConfigKey = true
			currentKey = p.trim(line[0:equalPos])
			valuePart := p.trim(line[equalPos+1:])

			isParsingMultiline = p.isMultiline(valuePart)
			if isParsingMultiline {
				keyValue.WriteString(p.cutOffSlash(valuePart))
				lineNumber++
				continue
			}

			keyValue.WriteString(valuePart)
		}

		if isConfigKey {
			expandedValue, err := p.expandVariableReferences(keyValue.String(), m)
			if err != nil {
				return nil, err
			}
			m[currentKey] = expandedValue
			keyValue.Reset()
			isConfigKey = false
		}

		lineNumber++
	}

	return m, nil
}
