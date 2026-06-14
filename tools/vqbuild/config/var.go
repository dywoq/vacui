// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package config

type VarInfo struct {
	Required bool
}

type GuideMap map[string]VarInfo

// HasRequiredVars iterates over gm and checks
// if key from gm is present in m.
//
// Returns empty slice and true, if len(missingRequired) is 0.
func HasRequiredVars(m map[string]string, gm GuideMap) (missingRequired []string, has bool) {
	if len(m) == 0 {
		return
	}
	for gk, gv := range gm {
		_, found := m[gk]
		if !found && gv.Required {
			missingRequired = append(missingRequired, gk)
		}
	}
	has = len(missingRequired) == 0
	return
}
