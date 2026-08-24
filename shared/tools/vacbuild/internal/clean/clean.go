// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package clean

import (
	"fmt"
	"os/exec"
	"path"
	"slices"

	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/config"
	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/crosscompile"
	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/mmake"
)

// Module cleans build artifacts in the module, its dependencies and sub-modules
// (if it is workspace) recursively. 
// 
// Module decodes the vacbuild.toml file in the directory. It generates a Make
// command and executes it with dir as the working directory. It recursively
// cleans dependencies if they are specified in the configuration. If the module
// type is [config.ModuleWorkspace], the function cleans workspace modules recursively.
func ModuleWithToolchain(dir string, t *crosscompile.Toolchain) error {
	moduleFile := path.Join(dir, "vacbuild.toml")
	conf, err := config.ParseModule(moduleFile)
	if err != nil {
		return err
	}

	switch conf.General.Type {
	case config.ModuleWorkspace:
		for _, m := range conf.Info.Workspace.Modules {
			err := ModuleWithToolchain(path.Join(dir, m), t)
			if err != nil {
				return fmt.Errorf("could not clean a module from the list: %v", err)
			}
		}
		return nil
	case config.ModuleRegular:
		for _, d := range conf.Info.Regular.Dependencies {
			err := ModuleWithToolchain(path.Join(dir, d), t)
			if err != nil {
				return fmt.Errorf("could not clean a dependency: %v", err)
			}
		}
		name, args := mmake.GenerateCommandWithToolchain(conf, t)
		cmd := exec.Command(name, slices.Concat([]string{"clean"}, args)...)
		cmd.Dir = dir
		output, err := cmd.CombinedOutput()
		if err != nil {
			fmt.Printf("Failed to clean the module %q:\n%s", dir, string(output))
			return err
		}
		return nil
	default:
		return fmt.Errorf("unknown type in the module %q: %v", dir, conf.General.Type)
	}
}
