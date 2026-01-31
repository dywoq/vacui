// Copyright 2026 dywoq
//
// This code is released under the Apache License 2.0:
// https://www.apache.org/licenses/LICENSE-2.0
//
// Repository:
// https://github.com/dywoq/vacui

// Package root provides functions to manage Vacui CPU folder.
package root

import (
	"fmt"
	"os"
)

// Dir returns a path to the Vacui CPU folder.
// Returns an error if it failed to get home directory.
func Dir() (string, error) {
	home, err := os.UserHomeDir()
	if err != nil {
		return "", err
	}
	return fmt.Sprintf("%s/.vacui/cpu", home), nil
}

// Create creates the Vacui CPU folder if it doesn't exists.
// Returns an error if it failed to get the folder path, or create folder.
func Create() error {
	dir, err := Dir()
	if err != nil {
		return err
	}
	if _, err := os.Stat(dir); os.IsNotExist(err) {
		err = os.MkdirAll(dir, 0755)
		if err != nil {
			return err
		}
	}
	return nil
}
