// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui

package main

import (
	"fmt"
	"os"

	"github.com/dywoq/vacui/tools/vacuicli/internal/cmd"
)

func main() {
	if err := cmd.Root().Execute(); err != nil {
		fmt.Printf("Failed to execute root command: %v\n", err)
		os.Exit(1)
	}
}
