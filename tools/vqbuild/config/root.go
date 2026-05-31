// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package config

import (
	"os"

	"github.com/pelletier/go-toml"
)

type Root struct {
	Dirs []string `toml:"dirs"`
}

// ParseModule reads root VQBuild configuration file from given path,
// and parses it.
func ParseRoot(path string) (*Root, error) {
	r := &Root{}
	bytes, err := os.ReadFile(path)
	if err != nil {
		return nil, err
	}
	err = toml.Unmarshal(bytes, r)
	if err != nil {
		return nil, err
	}
	return r, nil
}
