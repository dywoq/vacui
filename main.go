// Copyright 2026 dywoq
//
// This code is released under the Apache License 2.0:
// https://www.apache.org/licenses/LICENSE-2.0
//
// Repository:
// https://github.com/dywoq/vacui

package main

import (
	"os"

	"github.com/dywoq/vacui/internal/cmd"
	"github.com/dywoq/vacui/internal/terminal"
)

func main() {
	if err := cmd.Root().Execute(); err != nil {
		terminal.Errorf("Failed to execute root command: %v\n", err)
		os.Exit(1)
	}
}
