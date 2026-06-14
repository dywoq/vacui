// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package manage

import (
	"fmt"
	"os/exec"
	"path/filepath"
)

func CompileDb(folder string) error {
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
			err := CompileDb(subfolder)
			if err != nil {
				return err
			}
		}
	}

	// Generate make command.
	//
	// Empty string is passed to manually insert make command
	// and avoid shell issues such as:
	//
	// 		[dywoq@ArchLinux vqbuild]$ go run . compiledb test
	// 		[bear -- make clean all TARGET=testapp KIND=app SOURCES=main.cxx] test
	// 		Failed to generate compile_commands.json file in "test": exit status 2:
	// 		make: *** No rule to make target 'clean all'.  Stop.
	cmdName, cmdArgs := genMakeCommand("", false, folder, v)

	// Run bear command to generate compile commands
	bearArgs := append([]string{"--", cmdName}, cmdArgs...)
	bearArgs = append(bearArgs, "clean", "all")
	cmd := exec.Command("bear", bearArgs...)
	cmd.Dir = folder

	output, err := cmd.CombinedOutput()
	if err != nil {
		return fmt.Errorf("%v:\n%s", err, string(output))
	}

	return nil
}
