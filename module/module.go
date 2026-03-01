// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

// Package module defines a standard interface for SDK modules.
package module

type (
	// Initializer defines a method for initializing new module.
	Initializer interface {
		Init() error
	}

	// Cleaner defines a method fo cleaning up module resources.
	Cleaner interface {
		Clean()
	}

	// Module is part of the SDK, and responsible for one thing.
	Module interface {
		Initializer
		Cleaner
	}
)
