// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package manage

import (
	"fmt"
	"os/exec"
	"path/filepath"
)

// Clean parses the config file in folder and executes "make" command,
// providing config values to it. It cleans build artifacts.
//
// The function recursively calls [Clean] function, if there are dependencies.
func Clean(folder string) error {
	v, err := getConfigValues(folder)
	if err != nil {
		return err
	}

	// Clean dependencies before the main target
	if v.Depends != nil {
		for _, depend := range *v.Depends {
			if depend == folder {
				return fmt.Errorf("listing main target as dependency is not allowed: %v", *v.Depends)
			}

			subfolder := filepath.Join(folder, depend)
			err := Clean(subfolder)
			if err != nil {
				return err
			}
		}
	}

	// Run make command
	cmdName, cmdArgs := genMakeCommand("clean", true, folder, v)
	cmd := exec.Command(cmdName, cmdArgs...)
	output, err := cmd.CombinedOutput()
	if err != nil {
		return fmt.Errorf("%v:\n%s", err, string(output))
	}

	return nil
}
