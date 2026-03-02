// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package component

import "github.com/dywoq/vacui/runtime/lifecycle"

// Component is part of the SDK runtime, which is base of all components in runtime.
// It helps keep things modular.
type Component interface {
	// Life-cycle
	lifecycle.Manager
	lifecycle.StateCleaner
	lifecycle.StateGetter
	lifecycle.StateSetter

	// ID management
	IDGetter
	IDSetter
}
