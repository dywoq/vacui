// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package manage

import (
	"strings"

	"github.com/dywoq/vacui/tools/vqbuild/config"
)

func genMakeCommandJoin(strs ...string) string {
	return strings.Join(strs, "")
}

func genMakeCommand(makeCommand string, specifyFolder bool, folder string, v *config.Values) (string, []string) {
	args := []string{
		makeCommand,
		genMakeCommandJoin("TARGET=", v.Target),
		genMakeCommandJoin("KIND=", v.Kind),
		genMakeCommandJoin("SOURCES=", strings.Join(v.Sources, " ")),
		genMakeCommandJoin("BUILD_DIR=", v.BuildDir),
		genMakeCommandJoin("OBJECTS_DIR=", v.ObjectsDir),
	}

	if specifyFolder {
		args = append(args, "-C", folder)
	}

	return "make", args
}
