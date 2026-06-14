// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package manage

import (
	"fmt"
	"os"
	"os/exec"
	"path"
	"path/filepath"

	"github.com/dywoq/vacui/tools/vqbuild/config"
)

// Build parses the config file in folder and executes "make" command,
// providing config values to it. It builds the target.
//
// The function recursively calls Build function, if there are dependencies.
func Build(folder string) error {
	p := config.NewParser()

	// Join paths
	configPath := path.Join(folder, "vqbuild")

	// Open file and read it
	f, err := os.Open(configPath)
	if err != nil {
		return err
	}
	err = p.Read(f)
	if err != nil {
		return err
	}

	// Get the config map and its values
	m, err := p.Parse()
	if err != nil {
		return err
	}
	v, err := config.NewValues(m)
	if err != nil {
		return err
	}

	// Build dependencies before the main target
	if v.Depends != nil {
		for _, depend := range *v.Depends {
			if depend == folder {
				return fmt.Errorf("listing main target as dependency is not allowed: %v", *v.Depends)
			}

			subfolder := filepath.Join(folder, depend)
			err := Build(subfolder)
			if err != nil {
				return err
			}
		}
	}

	// Run make command
	cmdName, cmdArgs := genMakeCommand("all", true, folder, v)
	cmd := exec.Command(cmdName, cmdArgs...)
	output, err := cmd.CombinedOutput()
	if err != nil {
		return fmt.Errorf("%v:\n%s", err, string(output))
	}

	return nil
}

