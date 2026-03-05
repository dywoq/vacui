// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package process

import (
	"github.com/dywoq/vacui/errors"
	"github.com/dywoq/vacui/internal/info"
	"github.com/dywoq/vacui/runtime/internal/startup"
	"github.com/dywoq/vacui/runtime/lifecycle"
)

func Start() error {
	if info.Runtime.Process.On.Load() {
		return errors.ErrRuntimeProcessOn
	}

	err := setupSubsystems()
	if err != nil {
		return err
	}

	info.Runtime.Process.On.Store(true)
	return nil
}

func Shutdown() error {
	if !info.Runtime.Process.On.Load() {
		return errors.ErrRuntimeProcessOff
	}

	cleanSubsystems()

	info.Runtime.Process.On.Store(false)
	return nil
}

func setupSubsystems() error {
	if len(startup.Subsystems) == 0 {
		return nil
	}
	ok := true
	err := error(nil)
	initialized := []lifecycle.Manager{}
	for _, pre := range startup.Subsystems {
		err = pre.Init()
		if err != nil {
			ok = false
			break
		}
		initialized = append(initialized, pre)
	}

	if ok && err == nil {
		return nil
	}

	for i := len(initialized) - 1; i >= 0; i-- {
		startup.Subsystems[i].Clean()
	}

	return err
}

func cleanSubsystems() {
	if len(startup.Subsystems) == 0 {
		return
	}
	for i := len(startup.Subsystems) - 1; i >= 0; i-- {
		startup.Subsystems[i].Clean()
	}
}
