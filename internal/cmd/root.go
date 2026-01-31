// Copyright 2026 dywoq
//
// This code is released under the Apache License 2.0:
// https://www.apache.org/licenses/LICENSE-2.0
//
// Repository:
// https://github.com/dywoq/vacui

package cmd

import (
	"github.com/dywoq/vacui/internal/cmd/setup"
	"github.com/spf13/cobra"
)

func Root() *cobra.Command {
	root := &cobra.Command{
		Use:   "vacui",
		Short: "Run and manage Vacui CPU projects",
	}
	root.AddCommand(setup.Cmd())
	return root
}
