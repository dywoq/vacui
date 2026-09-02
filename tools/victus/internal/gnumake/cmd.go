// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package gnumake

import (
	"errors"
	"fmt"
	"strings"

	"github.com/dywoq/vacui/tools/victus/internal/module"
	"github.com/dywoq/vacui/tools/victus/internal/toolchain"
)

// Cmd contains GNU Make command information, such as executable and
// arguments. It is generated and provided by [GenerateCmd] function.
type Cmd struct {
	Executable string
	Args       []string
}

type BuildType string

const (
	BuildRelease BuildType = "release"
	BuildDebug   BuildType = "debug"
)

// IsValid checks whether b is a valid build type.
func (b BuildType) IsValid() bool {
	switch b {
	case BuildRelease, BuildDebug:
		return true
	default:
		return false
	}
}

// GenerateCmd uses the provided module and toolchain to generate a GNU Make
// command executable and arguments. Returns an error if m.General.Type is
// [module.TypeRegular].
func GenerateCmd(rules []string, m *module.Config, t *toolchain.Toolchain, b BuildType) (*Cmd, error) {
	if m.General.Type != module.TypeRegular {
		return nil, errors.New("regular modules are supported only")
	}
	if !b.IsValid() {
		return nil, errors.New("non-valid build type")
	}

	c := &Cmd{}
	c.Executable = "make"
	c.Args = []string{}

	c.Args = append(c.Args, rules...)
	c.Args = append(c.Args,
		fmt.Sprintf("TARGET_PATH=%s", m.Info.Regular.TargetPath),
		fmt.Sprintf("OBJECTS_DIR=%s", m.Info.Regular.ObjectsDir),
		fmt.Sprintf("SOURCES=%s", strings.Join(m.Info.Regular.Sources, " ")),
	)
	c.Args = append(c.Args,
		fmt.Sprintf("TOOLCHAIN_COMPILER_C=%s", t.CompilerC),
		fmt.Sprintf("TOOLCHAIN_COMPILER_CXX=%s", t.CompilerCxx),
		fmt.Sprintf("TOOLCHAIN_LINKER=%s", t.Linker),
		fmt.Sprintf("TOOLCHAIN_ASSEMBLY=%s", t.Assembly),
		fmt.Sprintf("TOOLCHAIN_ADDITIONAL_FLAGS_C=%s", strings.Join(t.AdditionalFlagsC, " ")),
		fmt.Sprintf("TOOLCHAIN_ADDITIONAL_FLAGS_CXX=%s", strings.Join(t.AdditionalFlagsCxx, " ")),
		fmt.Sprintf("TOOLCHAIN_ADDITIONAL_FLAGS_LINKER=%s", strings.Join(t.AdditionalFlagsLinker, " ")),
		fmt.Sprintf("TOOLCHAIN_ADDITIONAL_FLAGS_ASSEMBLY=%s", strings.Join(t.AdditionalFlagsAssembly, " ")),
	)

	return c, nil
}
