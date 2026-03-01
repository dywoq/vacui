// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package core

import "github.com/dywoq/vacui/internal/runtime"

func Start() error {
	return runtime.Start()
}

func Exit() error {
	return runtime.Shutdown()
}
