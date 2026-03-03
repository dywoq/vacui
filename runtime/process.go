// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package runtime

import "github.com/dywoq/vacui/runtime/internal/process"

func Start() error { return process.Start() }

func Shutdown() error { return process.Shutdown() }
