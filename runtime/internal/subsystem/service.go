// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

package subsystem

import (
	"sync"

	"github.com/dywoq/vacui/errors"
	"github.com/dywoq/vacui/internal/info"
	"github.com/dywoq/vacui/runtime/lifecycle"
	"github.com/dywoq/vacui/service"
)

type ServiceController struct {
	mu   sync.Mutex
	list []service.Service
}

var SCInst *ServiceController = NewSericeController()

func NewSericeController() *ServiceController {
	sc := &ServiceController{}
	sc.mu = sync.Mutex{}
	sc.list = []service.Service{}
	return sc
}

func (s *ServiceController) Add(srv service.Service) error {
	s.mu.Lock()
	defer s.mu.Unlock()
	if info.Runtime.Process.On.Load() {
		return errors.ErrRuntimeProcessOn
	}
	srv.SetID(service.ID(len(s.list)))
	s.list = append(s.list, srv)
	return nil
}

func (s *ServiceController) Init() error {
	s.mu.Lock()
	defer s.mu.Unlock()
	if len(s.list) == 0 {
		return nil
	}
	err := error(nil)
	for _, srv := range s.list {
		srv.CleanLifecycleState()
		err = srv.Init()
		if err != nil {
			srv.SetLifecycleState(lifecycle.StateFailed)
			break
		}
		srv.SetLifecycleState(lifecycle.StateInitialized)
	}
	if err == nil {
		return nil
	}
	return err
}

func (s *ServiceController) Clean() {
	s.mu.Lock()
	defer s.mu.Unlock()
	for _, srv := range s.list {
		if srv.GetLifecycleState()&lifecycle.StateInitialized != 0 {
			srv.Clean()
		}
	}
}

// NOTE: Since struct methods can't have its type parameters,
// we have to put it out of scope.
//
// If the proposal is implemented, SCGetService will be deprecated.
func SCGetService[T any](s *ServiceController) (T, error) {
	s.mu.Lock()
	defer s.mu.Unlock()

	var zero T

	for _, service := range s.list {
		if asserted, ok := service.(T); ok {
			return asserted, nil
		}
	}

	return zero, errors.ErrRuntimeServiceNotFound
}
