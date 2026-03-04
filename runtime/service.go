// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package runtime

import (
	"github.com/dywoq/vacui/runtime/internal/subsystem"
	"github.com/dywoq/vacui/service"
)

func AddService(s service.Service) error {
	return subsystem.SCInst.Add(s)
}

func GetService[T any]() (*T, error) {
	return subsystem.SCGetService[T](subsystem.SCInst)
}
