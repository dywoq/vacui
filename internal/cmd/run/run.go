// Copyright 2026 dywoq
//
// This code is released under the Apache License 2.0:
// https://www.apache.org/licenses/LICENSE-2.0
//
// Repository:
// https://github.com/dywoq/vacui

package run

import (
	"os"

	"github.com/dywoq/vacui/internal/config"
	"github.com/dywoq/vacui/internal/cpu"
	"github.com/dywoq/vacui/internal/terminal"
	"github.com/spf13/cobra"
)

func Cmd() *cobra.Command {
	run := &cobra.Command{
		Use:   "run",
		Short: "Run Vacui CPU project",
		Long:  "Run Vacui CPU project. Make sure you defined \"entry\" field in vacui_cpu.toml configuration file.",
		Run: func(cmd *cobra.Command, args []string) {
			f, err := os.Open("vacui_cpu.toml")
			if err != nil {
				terminal.Errorf("Can't open vacui_cpu.toml file: %v\n", err)
				os.Exit(1)
			}

			config, meta, err := config.DecodeRoot(f)
			if err != nil {
				terminal.Errorf("Failed to decode vacui_cpu.toml file: %v\n", err)
				os.Exit(1)
			}

			if !meta.IsDefined("entry") {
				terminal.Errorln("Expected 'entry' field in vacui_cpu.toml file")
				os.Exit(1)
			}

			runner := &cpu.Runner{}
			err = runner.RunFile(config.Entry)
			if err != nil {
				terminal.Errorf("Failed to run entry \"%s\" file: %v\n", config.Entry, err)
				os.Exit(1)
			}
		},
	}
	return run
}
