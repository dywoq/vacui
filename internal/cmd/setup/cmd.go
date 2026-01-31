// Copyright 2026 dywoq
//
// This code is released under the Apache License 2.0:
// https://www.apache.org/licenses/LICENSE-2.0
//
// Repository:
// https://github.com/dywoq/vacui

package setup

import (
	"os"

	"github.com/dywoq/vacui/internal/root"
	"github.com/dywoq/vacui/internal/terminal"
	"github.com/spf13/cobra"
)

func Cmd() *cobra.Command {
	root := &cobra.Command{
		Use:   "setup",
		Short: "Setup Vacui CPU before running other commands",
		Run: func(cmd *cobra.Command, args []string) {
			// Create root directory if it exists
			err := root.Create()
			if err != nil {
				terminal.Errorf("Failed to create root directory: %v", err)
				os.Exit(1)
			}
			terminal.Infoln("Successfully created root directory")
		},
	}
	return root
}
