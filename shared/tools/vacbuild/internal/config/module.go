// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package config

import (
	"os"

	"github.com/BurntSushi/toml"
)

// Module contains the module configuration fields.
type Module struct {
	General struct {
		TargetPath   string   `toml:"target_path"`
		Sources      []string `toml:"sources"`
		ObjsDir      string   `toml:"objs_dir"`
		Dependencies []string `toml:"dependencies"`
	} `toml:"general"`
	CustomInfo map[string]string `toml:"custom_info"`
}

// ParseModule reads the file and decodes it, returning a filled [Module].
// The returned instance is filled only if the function decoded the file successfully.
func ParseModule(file string) (*Module, error) {
	bytes, err := os.ReadFile(file)
	if err != nil {
		return nil, err
	}
	var module *Module
	_, err = toml.Decode(string(bytes), &module)
	return module, err
}
