// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package compiledb

import (
	"fmt"
	"os/exec"
	"path"
	"slices"

	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/config"
	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/crosscompile"
	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/mmake"
)

// GenerateInModule creates and generates a compilation database
// (compile_commands.json) in the specified module directory. It also builds
// the module.
func GenerateInModule(dir string, toolchain string) error {
	t, err := crosscompile.ParseToolchain(toolchain)
	if err != nil {
		return err
	}
	m, err := config.ParseModule(path.Join(dir, "vacbuild.toml"))
	if err != nil {
		return err
	}
	name, args := mmake.GenerateCommandWithToolchain(m, t)
	cmd := exec.Command("bear", slices.Concat([]string{"--"}, []string{name}, args)...)
	cmd.Dir = dir
	output, err := cmd.CombinedOutput()
	if err != nil {
		fmt.Printf("failed to generate the compilation database:\n%s\n", string(output))
		return err
	}
	return nil
}
