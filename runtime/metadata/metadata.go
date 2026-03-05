// Copyright 2026 dywoq - Apache License 2.0
// Part of Vacui SDK: https://github.com/dywoq/vacui

// Package metadata contains declarations of the game metadata.
package metadata

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
