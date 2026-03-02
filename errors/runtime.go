// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package errors

import (
	"errors"
)

var (
	ErrRuntimeProcessOn  = errors.New("vacui: runtime: process is already running")
	ErrRuntimeProcessOff = errors.New("vacui: runtime: process is not active")
)
