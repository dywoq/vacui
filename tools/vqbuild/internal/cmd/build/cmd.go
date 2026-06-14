// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package build

import (
	"fmt"
	"os"

	"github.com/dywoq/vacui/tools/vqbuild/manage"
	"github.com/spf13/cobra"
)

func Cmd() *cobra.Command {
	root := &cobra.Command{
		Use:   "build [folder]",
		Short: "Parse config files and run Makefile in folder to build target",
		Args:  cobra.ExactArgs(1),
		Run: func(cmd *cobra.Command, args []string) {
			folder := args[0]
			err := manage.Build(folder)
			if err != nil {
				fmt.Fprintf(os.Stderr, "Failed to build %q: %v\n", folder, err)
				os.Exit(1)
			}
		},
	}
	return root
}
