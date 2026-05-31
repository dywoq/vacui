// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package config

import (
	"os"

	"github.com/pelletier/go-toml"
)

type Module struct {
	Flags   []string `toml:"flags"`
	Sources []string `toml:"sources"`
}

// ParseModule reads file from given path, and parses it.
func ParseModule(path string) (*Module, error) {
	m := &Module{}
	bytes, err := os.ReadFile(path)
	if err != nil {
		return nil, err
	}
	err = toml.Unmarshal(bytes, m)
	if err != nil {
		return nil, err
	}
	return m, nil
}
