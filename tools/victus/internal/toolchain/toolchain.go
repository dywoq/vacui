package toolchain

import (
	"io"
	"os"

	"github.com/pelletier/go-toml"
)

type Toolchain struct {
	CompilerC               string   `toml:"compiler_c"`
	CompilerCxx             string   `toml:"compiler_cxx"`
	Linker                  string   `toml:"linker"`
	Assembly                string   `toml:"assembly"`
	AdditionalFlagsC        []string `toml:"additional_flags_c"`
	AdditionalFlagsCxx      []string `toml:"additional_flags_cxx"`
	AdditionalFlagsLinker   []string `toml:"additional_flags_linker"`
	AdditionalFlagsAssembly []string `toml:"additional_flags_assembly"`
}

// ParseWithReader decodes content using the provided [io.Reader].
// It assumes content uses TOML configuration format. Returns an error
// if it failed to do so.
func ParseWithReader(r io.Reader) (*Toolchain, error) {
	var t Toolchain
	err := toml.NewDecoder(r).Decode(&t)
	if err != nil {
		return nil, err
	}
	return &t, nil
}

// ParseFile opens a file handle. The function provides it as a reader
// to [ParseWithReader]. Returns an error if it failed to open the file,
// or [ParseWithReader] returns an error.
func ParseFile(filepath string) (*Toolchain, error) {
	f, err := os.Open(filepath)
	if err != nil {
		return nil, err
	}
	t, err := ParseWithReader(f)
	if err != nil {
		return nil, err
	}
	return t, nil
}
