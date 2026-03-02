// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package lifecycle

// Manager defines two methods for managing life-cycle of object.
type Manager interface {
	Init() error
	Clean()
}
