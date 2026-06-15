// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package manage

import (
	"os"
	"path"
	"strings"

	"github.com/dywoq/vacui/tools/vqbuild/internal/config"
)

func genMakeCommandJoin(strs ...string) string {
	return strings.Join(strs, "")
}

func genMakeCommand(makeCommand string, specifyFolder bool, folder string, v *config.Values) (string, []string) {
	args := []string{
		makeCommand,
		genMakeCommandJoin("TARGET=", v.Target),
		genMakeCommandJoin("SOURCES=", strings.Join(v.Sources, " ")),
		genMakeCommandJoin("BUILD_DIR=", v.BuildDir),
		genMakeCommandJoin("OBJECTS_DIR=", v.ObjectsDir),
	}

	if specifyFolder {
		args = append(args, "-C", folder)
	}

	return "make", args
}

func getConfigValues(folder string) (*config.Values, error) {
	p := config.NewParser()

	// Join paths
	configPath := path.Join(folder, "module")

	// Open file and read it
	f, err := os.Open(configPath)
	if err != nil {
		return nil, err
	}
	err = p.Read(f)
	if err != nil {
		return nil, err
	}

	// Get the config map and its values
	m, err := p.Parse()
	if err != nil {
		return nil, err
	}
	v, err := config.NewValues(m)
	if err != nil {
		return nil, err
	}

	return v, nil
}
