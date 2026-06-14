// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package build

import (
	"fmt"

	"github.com/dywoq/vacui/tools/vqbuild/internal/manage"
	"github.com/spf13/cobra"
)

func Cmd() *cobra.Command {
	root := &cobra.Command{
		Use:   "build [folder]",
		Short: "Parse config files and run Makefile in folder to build target",
		Args:  cobra.ExactArgs(1),
		RunE: func(cmd *cobra.Command, args []string) error {
			folder := args[0]
			
			arch, err := cmd.Flags().GetString("arch")
			if err != nil {
				return err
			}

			err = manage.Build(folder, arch)
			if err != nil {
				return fmt.Errorf("Failed to build %q: %v\n", folder, err)
			}
			return nil
		},
	}
	root.Flags().String("arch", "x86-64", "Specify architecture")

	return root
}
