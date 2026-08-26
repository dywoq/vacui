// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package mmake

import (
	"fmt"
	"strings"

	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/config"
	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/crosscompile"
)

type BuildType string

const (
	BuildRelease BuildType = "release"
	BuildDebug   BuildType = "debug"
)

// GenerateCommand wraps around the [GenerateCommandWithToolchain] function.
// It provides [crosscompile.DefaultToolchain] as a cross-compilation toolchain.
func GenerateCommand(m *config.Module, typ BuildType) (string, []string) {
	return GenerateCommandWithToolchain(m, crosscompile.DefaultToolchain(), typ)
}

// GenerateCommand uses the provided module and toolchain information to
// generate a Make command name and arguments.
func GenerateCommandWithToolchain(m *config.Module, t *crosscompile.Toolchain, typ BuildType) (cmd string, args []string) {
	cmd = "make"
	args = []string{
		fmt.Sprintf("SOURCES=%s", strings.Join(m.Info.Regular.Sources, " ")),
		fmt.Sprintf("TARGET_PATH=%s", m.Info.Regular.TargetPath),
		fmt.Sprintf("OBJS_DIR=%s", m.Info.Regular.ObjsDir),
		fmt.Sprintf("TOOLCHAIN_COMPILER_C=%s", t.CompilerC),
		fmt.Sprintf("TOOLCHAIN_COMPILER_CXX=%s", t.CompilerCxx),
		fmt.Sprintf("TOOLCHAIN_LINKER=%s", t.Linker),
		fmt.Sprintf("TOOLCHAIN_ASSEMBLY=%s", t.Assembly),
		fmt.Sprintf("TOOLCHAIN_ADDITIONAL_FLAGS_C=%s", strings.Join(t.AdditionalFlagsC, " ")),
		fmt.Sprintf("TOOLCHAIN_ADDITIONAL_FLAGS_CXX=%s", strings.Join(t.AdditionalFlagsCxx, " ")),
		fmt.Sprintf("TOOLCHAIN_ADDITIONAL_FLAGS_LINKER=%s", strings.Join(t.AdditionalFlagsLinker, " ")),
		fmt.Sprintf("TOOLCHAIN_ADDITIONAL_FLAGS_ASSEMBLY=%s", strings.Join(t.AdditionalFlagsAssembly, " ")),
	}
	for key, value := range m.Info.Regular.AdditionalMakeOptions {
		args = append(args, fmt.Sprintf("%s=%q", key, value))
	}
	if typ == BuildRelease {
		args = append(args, "BUILD_TYPE=RELEASE")
	}
	if typ == BuildDebug {
		args = append(args, "BUILD_TYPE=DEBUG")
	}
	return
}
