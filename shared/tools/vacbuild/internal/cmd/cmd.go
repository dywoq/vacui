// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package cmd

import (
	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/cmd/build"
	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/cmd/clean"
	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/cmd/compiledb"
	"github.com/spf13/cobra"
)

func Root() *cobra.Command {
	root := &cobra.Command{
		Use:   "vacbuild",
		Short: "Build system used across Vacui components and programs (C/C++)",
	}
	root.AddCommand(build.Cmd(), compiledb.Cmd(), clean.Cmd())
	return root
}
