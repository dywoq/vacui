// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package mmake

import (
	"fmt"
	"strings"

	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/config"
	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/crosscompile"
)

// GenerateCommand uses the provided module information to generate a Make
// command name and arguments.
func GenerateCommand(m *config.Module) (string, []string) {
	return GenerateCommandWithToolchain(m, crosscompile.DefaultToolchain())
}

// GenerateCommand uses the provided module information to generate a Make
// command name and arguments.
func GenerateCommandWithToolchain(m *config.Module, t *crosscompile.Toolchain) (cmd string, args []string) {
	cmd = "make"
	args = []string{
		fmt.Sprintf("SOURCES=%s", strings.Join(m.General.Sources, " ")),
		fmt.Sprintf("TARGET_PATH=%s", m.General.TargetPath),
		fmt.Sprintf("OBJS_DIR=%s", m.General.ObjsDir),
		fmt.Sprintf("TOOLCHAIN_COMPILER_C=%s", t.CompilerC),
		fmt.Sprintf("TOOLCHAIN_COMPILER_CXX=%s", t.CompilerCxx),
		fmt.Sprintf("TOOLCHAIN_LINKER=%s", t.Linker),
		fmt.Sprintf("TOOLCHAIN_ASSEMBLY=%s", t.Assembly),
		fmt.Sprintf("TOOLCHAIN_ADDITIONAL_FLAGS_C=%s", strings.Join(t.AdditionalFlagsC, " ")),
		fmt.Sprintf("TOOLCHAIN_ADDITIONAL_FLAGS_CXX=%s", strings.Join(t.AdditionalFlagsCxx, " ")),
		fmt.Sprintf("TOOLCHAIN_ADDITIONAL_FLAGS_LINKER=%s", strings.Join(t.AdditionalFlagsLinker, " ")),
		fmt.Sprintf("TOOLCHAIN_ADDITIONAL_FLAGS_ASSEMBLY=%s", strings.Join(t.AdditionalFlagsAssembly, " ")),
	}
	for key, value := range m.CustomInfo {
		args = append(args, fmt.Sprintf("%s=%q", key, value))
	}
	return
}
