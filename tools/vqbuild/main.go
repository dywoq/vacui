package main

import (
	"fmt"
	"os"

	"github.com/dywoq/vacui/tools/vqbuild/internal/cmd"
)

func main() {
	err := cmd.Root().Execute()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Failed to run root command: %v\n", err)
	}
}
