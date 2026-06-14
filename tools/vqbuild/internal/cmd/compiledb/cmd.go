// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package compiledb

import (
	"fmt"
	"os"

	"github.com/dywoq/vacui/tools/vqbuild/manage"
	"github.com/spf13/cobra"
)

func Cmd() *cobra.Command {
	root := &cobra.Command{
		Use:   "compiledb [folder]",
		Short: "Generate compile_commands.json file (C/C++ ONLY)",
		Args:  cobra.ExactArgs(1),
		Run: func(cmd *cobra.Command, args []string) {
			folder := args[0]
			err := manage.CompileDb(folder)
			if err != nil {
				fmt.Fprintf(os.Stderr, "Failed to generate compile_commands.json file in %q: %v\n", folder, err)
				os.Exit(1)
			}
		},
	}
	return root
}
