// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package service

type (
	// ID is a unique number for each service,
	// which is used to identify them.
	//
	// Not manually added - it's automatically generated and 
	// managed by runtime.
	ID uint32

	// Initializer defines a method to setup service.
	Initializer interface {
		Init() error
	}

	// Cleaner defines a method to run service procedures
	// of cleaning its resources.
	Cleaner interface {
		Clean() error
	}

	// IDGetter defines a getter of unique identifier from service.
	IDGetter interface {
		ID() ID
	}

	// IDSetter defines a setter for unique identifier for service.
	IDSetter interface {
		SetID(i ID)
	}

	// Service is part of the SDK, which is responsible
	// for one thing solely.
	Service interface {
		Initializer
		Cleaner
		IDGetter
		IDSetter
	}

	// Appender defines a method to append new services.
	Appender interface {
		AppendService(s Service) error
	}
)
