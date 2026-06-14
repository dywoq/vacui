// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package compiledb

import (
	"fmt"

	"github.com/dywoq/vacui/tools/vqbuild/manage"
	"github.com/spf13/cobra"
)

func Cmd() *cobra.Command {
	root := &cobra.Command{
		Use:   "compiledb [folder]",
		Short: "Generate compile_commands.json file (C/C++ ONLY)",
		Args:  cobra.ExactArgs(1),
		RunE: func(cmd *cobra.Command, args []string) error {
			folder := args[0]

			arch, err := cmd.Flags().GetString("arch")
			if err != nil {
				return err
			}

			err = manage.CompileDb(folder, arch)
			if err != nil {
				return fmt.Errorf("Failed to generate compile_commands.json file in %q: %v\n", folder, err)
			}

			return nil
		},
	}
	return root
}
