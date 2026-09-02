// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package cmd

import "github.com/spf13/cobra"

func Root() *cobra.Command {
	root := &cobra.Command{
		Use:   "victus",
		Short: "C/C++ Build orchestrator, which is specifically made for Vacui",
	}
	return root
}
