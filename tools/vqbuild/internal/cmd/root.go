// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package cmd

import "github.com/spf13/cobra"

func Root() *cobra.Command {
	root := &cobra.Command{
		Short: "Build orchestrator, made specifically for Vacui codebase",
	}
	return root
}
