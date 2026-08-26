// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package build

import (
	"fmt"

	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/build"
	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/crosscompile"
	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/mmake"
	"github.com/spf13/cobra"
)

func Cmd() *cobra.Command {
	cmd := &cobra.Command{
		Use:   "build [module-dir] [toolchain-path] [build-type]",
		Short: "Build your module",
		Args:  cobra.ExactArgs(3),
		RunE: func(cmd *cobra.Command, args []string) error {
			moduleDir := args[0]
			toolchainPath := args[1]
			buildType := args[2]
			t, err := crosscompile.ParseToolchain(toolchainPath)
			if err != nil {
				return fmt.Errorf("could not parse the toolchain file: %v", err)
			}
			err = build.ModuleWithToolchain(moduleDir, t, mmake.BuildType(buildType))
			if err != nil {
				return fmt.Errorf("building the module failed: %v", err)
			}
			return nil
		},
	}
	return cmd
}
