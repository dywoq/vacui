// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package main

import (
	"log"

	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/cmd"
)

func main() {
	if err := cmd.Root().Execute(); err != nil {
		log.Fatalf("could not run a root command: %v\n", err)
	}
}
