// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package config_test

import (
	"testing"

	"github.com/dywoq/vacui/tools/vqbuild/config"
)

func TestHasRequiredVars(t *testing.T) {
	tests := []struct {
		name string
		m    map[string]string
		gm   config.GuideMap
		want bool
	}{
		{
			"has required vars - true",
			map[string]string{"KEY_A": "FOO", "KEY_B": "XYZ"},
			config.GuideMap{"KEY_A": {true}},
			true,
		},
		{
			"no required vars",
			map[string]string{"KEY_D": "FOO", "KEY_B": "XYZ"},
			config.GuideMap{"KEY_A": {true}},
			false,
		},
		{
			"m is empty",
			map[string]string{},
			config.GuideMap{"KEY_A": {true}},
			false,
		},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			missingRequired, got := config.HasRequiredVars(test.m, test.gm)
			if got != test.want {
				t.Errorf("got %v, want %v (missing required vars: %v)", got, test.want, missingRequired)
			}
		})
	}
}
