// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package component

type (
	// Initializer defines a method to setup component.
	Initializer interface {
		Init() error
	}

	// Cleaner defines a method to run component procedures
	// of cleaning its resources.
	Cleaner interface {
		Clean() error
	}
)
