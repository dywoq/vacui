// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package lang

type Kind string

type TokenPos struct {
	Line int `json:"line"`
	Col  int `json:"col"`
	Idx  int `json:"idx"`
}

type Token struct {
	Literal string   `json:"literal"`
	Kind    Kind     `json:"kind"`
	Pos     TokenPos `json:"pos"`
}
