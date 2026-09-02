// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package cmd

import (
	"errors"
	"fmt"

	"github.com/dywoq/vacui/tools/victus/internal/gnumake"
	"github.com/dywoq/vacui/tools/victus/internal/routines"
	"github.com/dywoq/vacui/tools/victus/internal/toolchain"
	"github.com/spf13/cobra"
)

func Compiledb() *cobra.Command {
	c := &cobra.Command{
		Use:   "compiledb",
		Short: "Generate a compilation database inside workspace modules or a regular module",
		RunE: func(cmd *cobra.Command, args []string) error {
			toolchainPath, _ := cmd.Flags().GetString("toolchain")
			if len(toolchainPath) == 0 {
				return errors.New("no toolchain filepath specified")
			}
			moduleDir, _ := cmd.Flags().GetString("module")
			if len(moduleDir) == 0 {
				return errors.New("no module directory specified")
			}
			buildType, _ := cmd.Flags().GetString("build_type")
			if len(buildType) == 0 {
				return errors.New("no build type specified")
			}

			t, err := toolchain.ParseFile(toolchainPath)
			if err != nil {
				return fmt.Errorf("failed to parse the toolchain: %v", err)
			}
			err = routines.ModuleGenerateCompileDatabase(moduleDir, t, gnumake.BuildType(buildType))
			if err != nil {
				return err
			}
			fmt.Printf("Successfully generated a compilation database in the module %q\n", moduleDir)
			return nil
		},
	}
	c.Flags().String("module", "", "module directory")
	c.Flags().String("toolchain", "", "toolchain filepath")
	c.Flags().String("build_type", "debug", "build type")
	return c
}
