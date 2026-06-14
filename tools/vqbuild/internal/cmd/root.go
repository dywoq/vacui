// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package cmd

import (
	"github.com/dywoq/vacui/tools/vqbuild/internal/cmd/build"
	"github.com/dywoq/vacui/tools/vqbuild/internal/cmd/clean"
	"github.com/dywoq/vacui/tools/vqbuild/internal/cmd/compiledb"
	"github.com/spf13/cobra"
)

func Root() *cobra.Command {
	root := &cobra.Command{
		Use:   "vqbuild",
		Short: "Build orchestrator, made specifically for Vacui codebase",
	}
	root.AddCommand(build.Cmd(), clean.Cmd(), compiledb.Cmd())
	return root
}
