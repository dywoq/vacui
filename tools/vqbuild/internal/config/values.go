// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package config

import (
	"fmt"
	"strings"
)

type Values struct {
	Target     string
	Kind       string
	Sources    []string
	BuildDir   string
	ObjectsDir string
	Depends    *[]string
}

// NewValues checks if the map has required keys,
// and fills instance with values from the map.
func NewValues(m map[string]string) (*Values, error) {
	gm := GuideMap{
		"TARGET":      VarInfo{Required: true},
		"KIND":        VarInfo{Required: true},
		"SOURCES":     VarInfo{Required: true},
		"BUILD_DIR":   VarInfo{Required: true},
		"OBJECTS_DIR": VarInfo{Required: true},
		"DEPENDS":     VarInfo{Required: false},
	}
	if missingRequired, ok := HasRequiredVars(m, gm); !ok {
		return nil, fmt.Errorf("missing required vars: %v", missingRequired)
	}
	v := &Values{}
	v.Target = m["TARGET"]
	v.Kind = m["KIND"]
	v.Sources = strings.Split(m["SOURCES"], " ")
	v.BuildDir = m["BUILD_DIR"]
	v.ObjectsDir = m["OBJECTS_DIR"]
	if _, ok := m["DEPENDS"]; ok {
		depends := strings.Split(m["DEPENDS"], " ")
		v.Depends = &depends
	}

	return v, nil
}
