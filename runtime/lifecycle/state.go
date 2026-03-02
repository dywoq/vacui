// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package lifecycle

type (
	// State is a lifecycle state of object,
	// which is needed to understand - when to clean object or not.
	State uint32

	// StateSetter defines a method to set object lifecycle state.
	StateSetter interface {
		// SetLifecycleState sets a new lifecycle state to object,
		// using bitwise OR.
		SetLifecycleState(s State)
	}

	// StateGetter defines a method to get object lifecycle state.
	StateGetter interface {
		// GetLifecycleState returns object lifecycle state.
		GetLifecycleState(s State)
	}

	// StateCleaner defines a method to clean object lifecycle state.
	StateCleaner interface {
		// CleanLifecycleState cleans object lifecycle state.
		// Equals to setting state to zero, removing bits.
		CleanLifecycleState()
	}
)

const (
	StateInitialized State = 1 << 0
	StateCleaned     State = 1 << 1
	StateFailed      State = 1 << 2
)
