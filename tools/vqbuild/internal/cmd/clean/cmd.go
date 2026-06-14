// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package clean

import (
	"fmt"
	"os"

	"github.com/dywoq/vacui/tools/vqbuild/manage"
	"github.com/spf13/cobra"
)

func Cmd() *cobra.Command {
	root := &cobra.Command{
		Use:   "clean [folder]",
		Short: "Parse config files and run Makefile in folder to clean build artifacts",
		Args:  cobra.ExactArgs(1),
		Run: func(cmd *cobra.Command, args []string) {
			folder := args[0]
			err := manage.Clean(folder)
			if err != nil {
				fmt.Fprintf(os.Stderr, "Failed to clean build artifacts in %q: %v\n", folder, err)
				os.Exit(1)
			}
		},
	}
	return root
}
