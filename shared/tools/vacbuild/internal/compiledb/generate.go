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
// the module. If the module type is [config.ModuleWorkspace], the function
// recursively generates a compilation database in specified modules.
// If the module has dependencies, the function recursively generates a 
// compilation database in dependencies first.
func GenerateInModule(dir string, toolchain string) error {
	t, err := crosscompile.ParseToolchain(toolchain)
	if err != nil {
		return err
	}
	m, err := config.ParseModule(path.Join(dir, "vacbuild.toml"))
	if err != nil {
		return err
	}	
	if m.General.Type == config.ModuleWorkspace {
		if len(m.Workspace.Modules) != 0 {
			for _, m := range m.Workspace.Modules {
				err := GenerateInModule(path.Join(dir, m), toolchain)
				if err != nil {
					return fmt.Errorf("could not build a module from the list: %v", err)
				}
			}
		}
		return nil
	}
	
	if len(m.General.Dependencies) != 0 {
		for _, d := range m.General.Dependencies {
			err := GenerateInModule(path.Join(dir, d), toolchain)
			if err != nil {
				return fmt.Errorf("could not build a dependency: %v", err)
			}
		}
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
