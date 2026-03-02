// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package runtime

import "errors"

var (
	ErrProcessOn = errors.New("process is turned on")
	ErrProcessDisabled = errors.New("process is disabled")
)
