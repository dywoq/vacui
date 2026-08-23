// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package mmake

import (
	"fmt"
	"strings"

	"github.com/dywoq/vacui/shared/tools/vacbuild/internal/config"
)

// GenerateCommand uses the provided module information to generate a Make
// command name and arguments.
func GenerateCommand(m *config.Module) (cmd string, args []string) {
	cmd = "make"
	args = []string{
		fmt.Sprintf("SOURCES=%q", strings.Join(m.General.Sources, " ")),
		fmt.Sprintf("TARGET_PATH=%q", m.General.TargetPath),
		fmt.Sprintf("OBJS_DIR=%q", m.General.ObjsDir),
	}
	for key, value := range m.CustomInfo {
		args = append(args, fmt.Sprintf("%s=%q", key, value))
	}
	return
}
