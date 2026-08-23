// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package crosscompile

import (
	"os"

	"github.com/BurntSushi/toml"
)

type Toolchain struct {
	CompilerC   string `toml:"compiler_c"`
	CompilerCxx string `toml:"compiler_cxx"`
	Linker      string `toml:"linker"`
	Assembly    string `toml:"assembly"`
}

// ParseToolchain reads the file and decodes it, returning a filled [Toolchain].
// The returned instance is filled only if the function decoded the file successfully.
func ParseToolchain(file string) (*Toolchain, error) {
	bytes, err := os.ReadFile(file)
	if err != nil {
		return nil, err
	}
	var toolchain *Toolchain
	_, err = toml.Decode(string(bytes), &toolchain)
	return toolchain, err
}
