// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui

package build

import "github.com/spf13/cobra"

func Root() *cobra.Command {
	root := &cobra.Command{
		Use:   "build",
		Short: "Build operating system and its components in one command",
	}
	root.AddCommand(Os())
	root.AddCommand(Clean())
	return root
}
