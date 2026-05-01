// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui

package kconfig

import "github.com/spf13/cobra"

func Root() *cobra.Command {
	root := &cobra.Command{
		Use:   "kconfig",
		Short: "KConfig files management",
	}
	return root
}
