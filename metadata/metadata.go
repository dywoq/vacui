// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

// Package metadata contains declarations of the game metadata.
package metadata

import (
	"encoding/json"
	"os"
	"sync"
	"sync/atomic"

	"github.com/dywoq/vacui/errors"
)

type Version struct {
	View      string `json:"view"`
	Changelog string `json:"changelog"`
}

type Author struct {
	Name string `json:"name"`
}

type Metadata struct {
	Title    string    `json:"title"`
	Authors  []Author  `json:"authors"`
	Versions []Version `json:"versions"`
	License  string    `json:"license"`
	Links    []string  `json:"links"`
}

type Controller struct {
	mu     sync.Mutex
	m      *Metadata
	loaded atomic.Bool
}

func (c *Controller) LoadFromFile(path string) error {
	c.mu.Lock()
	defer c.mu.Unlock()
	if c.loaded.Load() {
		return errors.ErrMetadataLoaded
	}

	f, err := os.Open(path)
	if err != nil {
		return err
	}

	err = json.NewDecoder(f).Decode(&c.m)
	if err != nil {
		return err
	}

	c.loaded.Store(true)
	return nil
}

func (c *Controller) LoadFromInstance(m *Metadata) error {
	c.mu.Lock()
	defer c.mu.Unlock()
	if c.loaded.Load() {
		return errors.ErrMetadataLoaded
	}
	c.m = m
	c.loaded.Store(true)
	return nil
}

func (c *Controller) Metadata() *Metadata {
	c.mu.Lock()
	defer c.mu.Unlock()
	return c.m
}
