// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui

package cmd

import "github.com/spf13/cobra"

func Root() *cobra.Command {
	root := &cobra.Command{
		Use:   "vacuicli",
		Short: "Manage Vacui source code much easier",
	}
	return root
}
