// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package config

import (
	"fmt"
	"strings"
)

type Values struct {
	Target  string
	Kind    string
	Sources []string
	Depends []string
}

// NewValues checks if the map has required keys,
// and fills instance with values from the map.
func NewValues(m map[string]string) (*Values, error) {
	gm := GuideMap{
		"TARGET":  VarInfo{Required: true},
		"KIND":    VarInfo{Required: true},
		"SOURCES": VarInfo{Required: true},
		"DEPENDS": VarInfo{Required: true},
	}
	if missingRequired, ok := HasRequiredVars(m, gm); !ok {
		return nil, fmt.Errorf("missing required vars: %v", missingRequired)
	}
	v := &Values{}
	v.Target = m["TARGET"]
	v.Kind = m["KIND"]
	v.Sources = strings.Split(m["SOURCES"], " ")
	v.Depends = strings.Split(m["DEPENDS"], " ")
	return v, nil
}
