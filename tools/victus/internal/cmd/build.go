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

func Build() *cobra.Command {
	b := &cobra.Command{
		Use:   "build",
		Short: "Build workspace modules or a regular module",
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
			globalVarsMap := map[string]string{}
			globalVars, _ := cmd.Flags().GetStringSlice("global_vars")
			if len(globalVars) != 0 {
				m, err := gnumake.ParseVars(globalVars)
				if err != nil {
					return fmt.Errorf("failed to parse the provided global variables: %v", err)
				}
				globalVarsMap = m
			}

			t, err := toolchain.ParseFile(toolchainPath)
			if err != nil {
				return fmt.Errorf("failed to parse the toolchain: %v", err)
			}
			err = routines.ModuleBuild(moduleDir, t, gnumake.BuildType(buildType), globalVarsMap)
			if err != nil {
				return err
			}
			fmt.Printf("Successfully built the module %q\n", moduleDir)
			return nil
		},
	}
	b.Flags().String("module", "", "module directory")
	b.Flags().String("toolchain", "", "toolchain filepath")
	b.Flags().String("build_type", "debug", "build type")
	b.Flags().StringSlice("global_vars", []string{}, "custom global GNU Make variables. format: KEY1=VALUE,KEY2=VALUE")
	return b
}
