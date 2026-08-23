// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package build

import (
	"fmt"
	"os/exec"
	"path"

	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/config"
	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/crosscompile"
	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/mmake"
)

// Module decodes the vacbuild.toml file in the directory. It generates a Make
// command and executes it with dir as the working directory. It recursively
// builds dependencies if they are specified in the configuration. If the module
// type is [config.ModuleWorkspace], the function builds workspace modules recursively.
func ModuleWithToolchain(dir string, t *crosscompile.Toolchain) error {
	moduleFile := path.Join(dir, "vacbuild.toml")
	conf, err := config.ParseModule(moduleFile)
	if err != nil {
		return err
	}

	if conf.General.Type == config.ModuleWorkspace {
		if len(conf.Workspace.Modules) != 0 {
			for _, m := range conf.Workspace.Modules {
				err := ModuleWithToolchain(path.Join(dir, m), t)
				if err != nil {
					return fmt.Errorf("could not build a module from the list: %v", err)
				}
			}
		}
		return nil
	}

	if len(conf.General.Dependencies) != 0 {
		for _, d := range conf.General.Dependencies {
			err := ModuleWithToolchain(path.Join(dir, d), t)
			if err != nil {
				return fmt.Errorf("could not build a dependency: %v", err)
			}
		}
	}
	name, args := mmake.GenerateCommandWithToolchain(conf, t)
	cmd := exec.Command(name, args...)
	cmd.Dir = dir
	output, err := cmd.CombinedOutput()
	if err != nil {
		fmt.Printf("Failed to build the module %q:\n%s", dir, string(output))
		return err
	}
	return nil
}
