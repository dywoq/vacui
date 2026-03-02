// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package runtime

import "sync/atomic"

var processOn atomic.Bool

func init() {
	processOn.Store(false)
}

func Start() error {
	if processOn.Load() {
		return ErrProcessOn
	}
	processOn.Store(true)
	return nil
}

func Shutdown() error {
	if !processOn.Load() {
		return ErrProcessDisabled
	}
	processOn.Store(false)
	return nil
}
