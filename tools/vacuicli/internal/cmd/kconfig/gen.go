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
	return &cobra.Command{
		Use:   "gen",
		Short: "Generate KConfig header files",
		RunE: func(cmd *cobra.Command, args []string) error {
			for _, gm := range genModules {
				moduleDir := filepath.Dir(gm.kconfig)

				if _, err := os.Stat(gm.config); errors.Is(err, os.ErrNotExist) {
					return fmt.Errorf("config %s file doesn't exist", gm.config)
				} else if err != nil {
					return err
				}

				if err := os.MkdirAll(filepath.Dir(gm.headerPath), os.ModePerm); err != nil {
					return fmt.Errorf("failed to create directory %s: %w", filepath.Dir(gm.headerPath), err)
				}

				configRel, err := filepath.Rel(moduleDir, gm.config)
				if err != nil {
					return fmt.Errorf("failed to make config path relative: %w", err)
				}

				headerRel, err := filepath.Rel(moduleDir, gm.headerPath)
				if err != nil {
					return fmt.Errorf("failed to make header path relative: %w", err)
				}

				kconfigFile := filepath.Base(gm.kconfig)

				genCmd := exec.Command("genconfig", kconfigFile, "--header-path", headerRel)
				genCmd.Dir = moduleDir
				genCmd.Env = append(os.Environ(), fmt.Sprintf("KCONFIG_CONFIG=%s", configRel))

				output, err := genCmd.CombinedOutput()
				if err != nil {
					return fmt.Errorf("failed to generate header file %s:\n%s", gm.headerPath, string(output))
				}

				fmt.Printf("Generated %s\n", gm.headerPath)
			}

			return nil
		},
	}
}
