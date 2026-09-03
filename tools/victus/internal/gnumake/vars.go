// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package gnumake

import (
	"fmt"
	"strings"
)

func ParseVars(vars []string) (map[string]string, error) {
	m := map[string]string{}
	for _, variable := range vars {
		trimmed := strings.TrimSpace(variable)
		if len(trimmed) == 0 {
			continue
		}
		equalIndex := strings.Index(trimmed, "=")
		if equalIndex == -1 {
			return nil, fmt.Errorf("cannot find the equal operator in the %q variable", variable)
		}
		name := strings.TrimSpace(trimmed[0 : equalIndex-1])
		value := strings.TrimSpace(trimmed[equalIndex+1:])
		m[name] = value
	}
	return m, nil
}
