// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package main

import (
	"fmt"
	"path/filepath"

	"github.com/dywoq/vacui/tools/vqbuild/config"
)

func main() {
	root, err := config.ParseRoot("vqbuild.toml")
	if err != nil {
		panic(err)
	}
	fmt.Println(root.Dirs)

	modules := []string{}
	for _, dir := range root.Dirs {
		modules = append(modules, filepath.Join(dir, "module.toml"))
	}

	fmt.Println(modules)
}
