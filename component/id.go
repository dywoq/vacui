// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package component

type (
	// ID is a unique number for each component,
	// which is used to identify them.
	//
	// Not manually added - it's automatically generated and
	// managed by runtime.
	ID uint32

	// IDGetter defines a getter of unique identifier from component.
	IDGetter interface {
		ID() ID
	}

	// IDSetter defines a setter for unique identifier for component.
	IDSetter interface {
		SetID(i ID)
	}
)
