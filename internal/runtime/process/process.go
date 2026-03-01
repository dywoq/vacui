// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package process

import "sync/atomic"

type process struct {
	on atomic.Bool
}

func (p *process) start() error {
	p.on.Store(true)
	return nil
}

func (p *process) shutdown() error {
	p.on.Store(false)
	return nil
}
