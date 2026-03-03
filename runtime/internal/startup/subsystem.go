// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package startup

import (
	"github.com/dywoq/vacui/runtime/internal/subsystem"
	"github.com/dywoq/vacui/runtime/lifecycle"
)

var Subsystems []lifecycle.Manager = []lifecycle.Manager{
	subsystem.SCInst,
}
