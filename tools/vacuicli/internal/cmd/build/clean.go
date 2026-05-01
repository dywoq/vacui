// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui

package build

import (
	"fmt"
	"os"
	"path/filepath"

	"github.com/spf13/cobra"
)

func Clean() *cobra.Command {
	clean := &cobra.Command{
		Use:   "clean",
		Short: "Clean build artifacts",
		Run: func(cmd *cobra.Command, args []string) {
			targets := map[string]struct{}{
				".build":      {},
				".xmake":      {},
				"vacui.img":   {},
				".config":     {},
				".config.old": {},
				"config.h":    {},
			}
			root := "."
			filepath.WalkDir(root, func(path string, d os.DirEntry, err error) error {
				if err != nil {
					return nil
				}
				name := d.Name()
				if _, ok := targets[name]; ok {
					err := os.RemoveAll(path)
					if err != nil {
						fmt.Fprintf(os.Stderr, "Failed to remove %s: %v\n", path, err)
					}
					if d.IsDir() {
						return filepath.SkipDir
					}
				}
				return nil
			})
		},
	}
	return clean
}
