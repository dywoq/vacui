// Copyright 2026 dywoq
//
// This code is released under the Apache License 2.0:
// https://www.apache.org/licenses/LICENSE-2.0
//
// Repository:
// https://github.com/dywoq/vacui

package config

import (
	"io"

	"github.com/BurntSushi/toml"
)

// Root represents the root configuration of any project.
type Root struct {
	Name        string `toml:"name"`
	Description string `toml:"description"`
	Entry       string `toml:"entry"`
	Version     string `toml:"version"`
}

func DecodeRoot(r io.Reader) (*Root, *toml.MetaData, error) {
	var root Root
	meta, err := toml.NewDecoder(r).Decode(&root)
	if err != nil {
		return nil, nil, err
	}
	return &root, &meta, nil
}
