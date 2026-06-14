// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package run

import "github.com/spf13/cobra"

func Cmd() *cobra.Command {
	root := &cobra.Command{
		Use:   "run",
		Short: "Parse config files and run Makefile with its config variables",
		Run:   func(cmd *cobra.Command, args []string) {
			
		},
	}
	return root
}
