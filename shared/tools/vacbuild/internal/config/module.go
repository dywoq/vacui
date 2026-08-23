// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package config

import (
	"github.com/BurntSushi/toml"
)

type ModuleType string

// Module contains the module configuration fields.
type Module struct {
	General struct {
		Type ModuleType `toml:"type"`
	} `toml:"general"`
	Info struct {
		Workspace struct {
			Modules []string `toml:"modules"`
		}
		Regular struct {
			TargetPath            string            `toml:"target_path"`
			Sources               []string          `toml:"sources"`
			ObjsDir               string            `toml:"objs_dir"`
			Dependencies          []string          `toml:"dependencies"`
			AdditionalMakeOptions map[string]string `toml:"additional_make_options"`
		} `toml:"regular"`
	}
}

const (
	ModuleRegular   ModuleType = "regular"
	ModuleWorkspace ModuleType = "workspace"
)

// ParseModule reads the file and decodes it, returning a filled [Module].
// The returned instance is filled only if the function decoded the file successfully.
func ParseModule(file string) (*Module, error) {
	var module *Module
	_, err := toml.DecodeFile(file, &module)
	return module, err
}
