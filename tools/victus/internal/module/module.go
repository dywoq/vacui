// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package module

// Workspace contains module workspace information.
type Workspace struct {
	Modules []string `toml:"modules"`
}

// Regular contains regular module information.
type Regular struct {
	TargetPath   string   `toml:"target_path"`
	ObjectsDir   string   `toml:"objects_dir"`
	Sources      []string `toml:"sources"`
	Dependencies []string `toml:"dependencies"`
}

// Type is used to identify a module type.
type Type string

// General contains general module information.
type General struct {
	Type Type `json:"type"`
}

// Info combines workspace and regular information instances.
// One of them is activated if the module type is either
// [TypeWorkspace] or [TypeRegular].
type Info struct {
	Workspace Workspace `toml:"workspace"`
	Regular   Regular   `toml:"regular"`
}

// Config contains module information, such as general information.
type Config struct {
	General General `toml:"general"`
	Info    Info    `toml:"info"`
}

const (
	TypeWorkspace Type = "workspace"
	TypeRegular   Type = "regular"
)
