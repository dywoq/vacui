// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package component

// Component is part of the SDK runtime, which is base of all components in runtime.
// It helps keep things modular.
type Component interface {
	// State management
	StateGetter
	StateSetter

	// Life-cycle management
	Initializer
	Cleaner

	// ID management
	IDGetter
	IDSetter
}
