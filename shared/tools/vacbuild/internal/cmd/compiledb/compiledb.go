// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package compiledb

import (
	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/compiledb"
	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/mmake"
	"github.com/spf13/cobra"
)

func Cmd() *cobra.Command {
	cmd := &cobra.Command{
		Use:   "compiledb",
		Short: "Compilation database management",
	}
	cmd.AddCommand(Generate())
	return cmd
}

func Generate() *cobra.Command {
	cmd := &cobra.Command{
		Use:   "generate [module-dir] [toolchain-path] [build-type]",
		Short: "Generate a compilation database for your module",
		Args:  cobra.ExactArgs(3),
		RunE: func(cmd *cobra.Command, args []string) error {
			moduleDir := args[0]
			toolchainPath := args[1]
			buildType := args[2]
			err := compiledb.GenerateInModule(moduleDir, toolchainPath, mmake.BuildType(buildType))
			if err != nil {
				return err
			}
			return nil
		},
	}
	return cmd
}
