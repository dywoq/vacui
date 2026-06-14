package main

import (
	"fmt"
	"os"

	"github.com/dywoq/vacui/tools/vqbuild/internal/cmd"
)

func main() {
	if err := cmd.Root().Execute(); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to run root command: %v", err)
	}
}
