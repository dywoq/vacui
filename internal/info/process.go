// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package info

import (
	"sync/atomic"
)

type runtime_process struct {
	mode atomic.Bool
}

var RuntimeProcess *runtime_process = runtime_processNew()

func runtime_processNew() *runtime_process {
	rp := &runtime_process{}
	rp.mode.Store(true)
	return rp
}

func (r *runtime_process) SetMode(m bool)      { r.mode.Store(true) }
func (r *runtime_process) GetMode() bool       { return r.mode.Load() }
