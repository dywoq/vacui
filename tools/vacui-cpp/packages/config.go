// Copyright 2026 Vacui - Apache License 2.0
// https://github.com/dywoq/vacui

package packages

import (
	"io"
	"io/fs"
	"os"

	"github.com/BurntSushi/toml"
)

// Type identifies the type of a package.
type Type string

type General struct {
	Type             Type   `toml:"type"`
	DefaultToolchain string `toml:"default_toolchain"`
	OutputFile       string `toml:"output_file"`
	ObjectsDir       string `toml:"objects_dir"`
}

type Config struct {
	General *General `toml:"general"`
}

const (
	TypeProgram Type = "program"
	TypeLibrary Type = "library"
)

// DecodeConfigReader reads the contents of the provided [io.Reader] and decodes it
// using [toml.Decode].
func DecodeConfigReader(r io.Reader) (*Config, toml.MetaData, error) {
	var c *Config
	content, err := io.ReadAll(r)
	if err != nil {
		return nil, toml.MetaData{}, err
	}
	m, err := toml.Decode(string(content), &c)
	if err != nil {
		return nil, toml.MetaData{}, err
	}
	return c, m, nil
}

// DecodeConfig wraps around [DecodeConfigReader]. DecodeConfig opens a file and provides
// [os.File] instance to [DecodeConfigReader].
func DecodeConfig(filepath string) (*Config, toml.MetaData, error) {
	f, err := os.Open(filepath)
	if err != nil {
		return nil, toml.MetaData{}, err
	}
	defer f.Close()
	return DecodeConfigReader(f)
}

// DecodeConfig wraps around [DecodeConfigReader]. DecodeConfig opens a file and provides
// [os.File] instance to [DecodeConfigReader].
func DecodeConfigFS(fs fs.FS, filepath string) (*Config, toml.MetaData, error) {
	f, err := fs.Open(filepath)
	if err != nil {
		return nil, toml.MetaData{}, err
	}
	return DecodeConfigReader(f)
}
