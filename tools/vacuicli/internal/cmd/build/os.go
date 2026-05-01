// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui

package build

import (
	"fmt"
	"os"
	"os/exec"
	"strings"

	"github.com/spf13/cobra"
)

func Os() *cobra.Command {
	os := &cobra.Command{
		Use:   "os",
		Short: "Build whole operating system",
		Run: func(cmd *cobra.Command, args []string) {
			runCmd("dd", "if=/dev/zero", "of=vacui.img", "bs=1M", "count=10")

			runCmd("make", "-C", "boot/sector", "clean", "all")

			runCmd("dd",
				"if=boot/sector/.build/vqboot_sector.bin",
				"of=vacui.img",
				"conv=notrunc",
				"count=1",
			)

			runCmd("xmake", "build", "vqboot_primary")

			runCmd("objcopy",
				"-O", "binary",
				".build/linux/x86_64/release/vqboot_primary",
				".build/vqboot_primary.bin",
			)

			runCmd("dd",
				"if=.build/vqboot_primary.bin",
				"of=vacui.img",
				"conv=notrunc",
				"seek=1",
			)

			runCmd("xmake", "build", "vqkrnl")

			runCmd("objcopy",
				"-O", "binary",
				".build/linux/x86_64/release/vqkrnl",
				".build/vqkrnl.bin",
			)

			runCmd("dd",
				"if=.build/vqkrnl.bin",
				"of=vacui.img",
				"conv=notrunc",
				"seek=2",
			)
		},
	}
	return os
}

func runCmd(name string, args ...string) {
	c := exec.Command(name, args...)
	output, err := c.CombinedOutput()
	if err != nil {
		argsStr := strings.Join(args, " ")
		fmt.Fprintf(os.Stderr, "Failed to run command: \"%s %s\":\n%v\n", name, argsStr, string(output))
		os.Exit(1)
	}
}
