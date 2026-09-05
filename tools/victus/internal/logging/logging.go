// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package logging

import (
	"fmt"
	"os"
	"sync"

	"github.com/fatih/color"
)

type Mode int

const (
	ModeEnabled Mode = iota
	ModeDisabled
)

var (
	modeMu sync.Mutex
	mode   Mode = ModeDisabled
)

func SetMode(m Mode) {
	modeMu.Lock()
	defer modeMu.Unlock()
	mode = m
}

func GetMode() Mode {
	modeMu.Lock()
	defer modeMu.Unlock()
	return mode
}

func Errorf(format string, v ...any) {
	modeMu.Lock()
	defer modeMu.Unlock()
	if mode == ModeDisabled {
		return
	}
	prefix := color.RedString("[error]")
	fmt.Fprintf(os.Stderr, "* %s: %s", prefix, fmt.Sprintf(format, v...))
}

func Infof(format string, v ...any) {
	modeMu.Lock()
	defer modeMu.Unlock()
	if mode == ModeDisabled {
		return
	}
	prefix := color.GreenString("[info]")
	fmt.Fprintf(os.Stderr, "* %s: %s", prefix, fmt.Sprintf(format, v...))
}

func Warnf(format string, v ...any) {
	modeMu.Lock()
	defer modeMu.Unlock()
	if mode == ModeDisabled {
		return
	}
	prefix := color.YellowString("[warn]")
	fmt.Fprintf(os.Stderr, "* %s: %s", prefix, fmt.Sprintf(format, v...))
}
