// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package registry

import "github.com/dywoq/vacui/component"

type (
	// Registry is part of the SDK, which only contains data/information,
	// and is thread-safe.
	// 
	// Registry is able to have its own methods for services 
	// to interact with. 
	Registry interface {
		component.Component
	}

	// Appender defines a method to append new registries.
	Appender interface {
		AppendRegistry(s Registry) error
	}
)
