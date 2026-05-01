// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui

package kconfig

import (
	"errors"
	"fmt"
	"os"
	"os/exec"
	"path/filepath"

	"github.com/spf13/cobra"
)

type genModule struct {
	kconfig    string
	config     string
	headerPath string
}

var genModules = []genModule{
	{"boot/primary/Kconfig", "boot/primary/.config", "boot/primary/include/generated/config.h"},
	{"krnl/Kconfig", "krnl/.config", "krnl/include/generated/config.h"},
}

func Gen() *cobra.Command {
	gen := &cobra.Command{
		Use:   "gen",
		Short: "Generate KConfig header files",
		Run: func(cmd *cobra.Command, args []string) {
			for _, genModule := range genModules {
				headerFolder := filepath.Dir(genModule.headerPath)

				if _, err := os.Stat(genModule.config); errors.Is(err, os.ErrNotExist) {
					fmt.Fprintf(os.Stderr, "error: Config %s file doesn't exist\n", genModule.config)
					os.Exit(1)
				}
				
				if err := os.MkdirAll(headerFolder, os.ModePerm); err != nil {
					fmt.Fprintf(os.Stderr, "error: Failed to create directory %s: %v\n", headerFolder, err)
					os.Exit(1)
				}

				cmd := exec.Command("genconfig", genModule.kconfig, "--header-path", genModule.headerPath)

				cmd.Env = append(os.Environ(), fmt.Sprintf("KCONFIG_CONFIG=%s", genModule.config))

				bytes, err := cmd.CombinedOutput()
				if err != nil {
					fmt.Fprintf(os.Stderr, "error: Failed to generate header file %s:\n%s\n", genModule.headerPath, string(bytes))
					os.Exit(1)
				}

				fmt.Printf("Generated %s\n", genModule.headerPath)
			}
		},
	}
	return gen
}
