// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package component

type (
	// State is a component state, which helps runtime to track the component.
	State uint16

	// StateGetter defines a method for getting state.
	StateGetter interface {
		GetState() State
	}

	// StateSetter defines a method for setting state, using bitwise operator OR.
	// It allows using multiple states.
	StateSetter interface {
		SetState(s State)
	}
)

const (
	StateInitialized State = 1 << 1
	StateRegistered  State = 1 << 2
)
