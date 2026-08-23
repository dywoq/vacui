// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package build

import (
	"fmt"
	"os/exec"
	"path"

	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/config"
	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/mmake"
)

// Module decodes the vacbuild.toml file in the directory. It recursively builds
// dependencies if they are specified in the configuration. The function generates a
// Make command and executes it with dir as the working directory.
func Module(dir string) error {
	moduleFile := path.Join(dir, "vacbuild.toml")
	config, err := config.ParseModule(moduleFile)
	if err != nil {
		return err
	}
	if len(config.General.Dependencies) != 0 {
		for _, d := range config.General.Dependencies {
			err := Module(path.Join(dir, d))
			if err != nil {
				return fmt.Errorf("could not build a dependency: %v", err)
			}
		}
	}
	name, args := mmake.GenerateCommand(config)
	cmd := exec.Command(name, args...)
	cmd.Dir = dir
	output, err := cmd.CombinedOutput()
	if err != nil {
		fmt.Printf("Failed to build the module %q:\n%s", dir, string(output))
		return err
	}
	return nil
}
