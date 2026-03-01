// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package service

import "github.com/dywoq/vacui/component"

type (
	// Service is part of the SDK, which is responsible
	// for doing one thing.
	Service interface {
		component.Component
	}

	// Appender defines a method to append new services.
	Appender interface {
		AppendService(s Service) error
	}
)
