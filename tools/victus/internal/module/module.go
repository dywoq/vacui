// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package module

import (
	"io"
	"os"

	"github.com/pelletier/go-toml"
)

// Workspace contains module workspace information.
type Workspace struct {
	Modules []string `toml:"modules"`
}

// Regular contains regular module information.
type Regular struct {
	TargetPath      string   `toml:"target_path"`
	ObjectsDir      string   `toml:"objects_dir"`
	Sources         []string `toml:"sources"`
	Dependencies    []string `toml:"dependencies"`
	ForcedToolchain string   `toml:"forced_toolchain"`
}

// Type is used to identify a module type.
type Type string

// General contains general module information.
type General struct {
	Type Type `json:"type"`
}

// Info combines workspace and regular information instances.
// One of them is activated if the module type is either
// [TypeWorkspace] or [TypeRegular].
type Info struct {
	Workspace Workspace `toml:"workspace"`
	Regular   Regular   `toml:"regular"`
}

// Config contains module information, such as general information.
type Config struct {
	General General `toml:"general"`
	Info    Info    `toml:"info"`
}

const (
	TypeWorkspace Type = "workspace"
	TypeRegular   Type = "regular"
)

// ParseWithReader decodes content using the provided [io.Reader].
// It assumes content uses TOML configuration format. Returns an error
// if it failed to do so.
func ParseWithReader(r io.Reader) (*Config, error) {
	var c Config
	err := toml.NewDecoder(r).Decode(&c)
	if err != nil {
		return nil, err
	}
	return &c, nil
}

// ParseFile opens a file handle. The function provides it as a reader
// to [ParseWithReader]. Returns an error if it failed to open the file,
// or [ParseWithReader] returns an error.
func ParseFile(filepath string) (*Config, error) {
	f, err := os.Open(filepath)
	if err != nil {
		return nil, err
	}
	c, err := ParseWithReader(f)
	if err != nil {
		return nil, err
	}
	return c, nil
}
