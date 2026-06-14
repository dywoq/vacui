// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package manage

import (
	"strings"

	"github.com/dywoq/vacui/tools/vqbuild/config"
)

func genMakeCommand(makeCommand string, specifyFolder bool, folder string, v *config.Values) (string, []string) {
	args := []string{
		makeCommand,
		strings.Join([]string{"TARGET=", v.Target}, ""),
		strings.Join([]string{"KIND=", v.Kind}, ""),
		strings.Join([]string{"SOURCES=", strings.Join(v.Sources, " ")}, ""),
	}

	if specifyFolder {
		args = append(args, "-C", folder)
	}

	return "make", args
}
