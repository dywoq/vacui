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

func CompileDb(folder string) error {
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

	fmt.Println(cmd.Args, cmd.Dir)

	output, err := cmd.CombinedOutput()
	if err != nil {
		return fmt.Errorf("%v:\n%s", err, string(output))
	}

	return nil
}
