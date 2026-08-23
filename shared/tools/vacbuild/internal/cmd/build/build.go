// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package build

import (
	"log"

	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/build"
	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/crosscompile"
	"github.com/spf13/cobra"
)

func Cmd() *cobra.Command {
	cmd := &cobra.Command{
		Use:   "build [module-dir] [toolchain-path]",
		Short: "Build your module",
		Args:  cobra.ExactArgs(2),
		Run: func(cmd *cobra.Command, args []string) {
			moduleDir := args[0]
			toolchainPath := args[1]
			t, err := crosscompile.ParseToolchain(toolchainPath)
			if err != nil {
				log.Fatalf("could not parse the toolchain file: %v", err)
			}
			err = build.ModuleWithToolchain(moduleDir, t)
			if err != nil {
				log.Fatalf("building the module failed: %v", err)
			}
		},
	}
	return cmd
}
