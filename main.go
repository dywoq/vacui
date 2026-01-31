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

	"github.com/dywoq/vacui/root"
	"github.com/dywoq/vacui/terminal"
)

func main() {
	err := root.Create()
	if err != nil {
		terminal.Errorf("Failed to create root directory: %v\n", err)
		os.Exit(1)
	}
}
