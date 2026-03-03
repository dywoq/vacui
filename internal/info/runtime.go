// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package info

import (
	"sync/atomic"

	"github.com/dywoq/vacui/runtime/lifecycle"
)

type (
	runtimeProcess struct {
		On atomic.Bool
	}
	runtimeLifecycle struct {
		Managers []lifecycle.Manager
	}
	runtime struct {
		Process   *runtimeProcess
		Lifecycle *runtimeLifecycle
	}
)

func newRuntimeProcess() *runtimeProcess {
	rp := &runtimeProcess{}
	rp.On.Store(false)
	return rp
}

func newRuntimeLifecycle() *runtimeLifecycle {
	rlc := &runtimeLifecycle{}
	rlc.Managers = []lifecycle.Manager{}
	return rlc
}

func newRuntime() *runtime {
	r := &runtime{}
	r.Process = newRuntimeProcess()
	r.Lifecycle = newRuntimeLifecycle()
	return r
}

var Runtime = newRuntime()
