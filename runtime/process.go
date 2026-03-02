// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package runtime

type process struct{}

var globalProcess *process = &process{}

func (p *process) start() error    { return nil }
func (p *process) shutdown() error { return nil }

func Start() error {
	return globalProcess.start()
}

func Shutdown() error {
	return globalProcess.shutdown()
}
