// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package service

import (
	"github.com/dywoq/vacui/runtime/lifecycle"
)

type (
	// Service is part of the SDK, which is responsible
	// for doing one thing.
	Service interface {
		// Life-cycle
		lifecycle.Manager
		lifecycle.StateCleaner
		lifecycle.StateGetter
		lifecycle.StateSetter

		// ID management
		IDGetter
		IDSetter
	}
)
