// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

package token

type Kind string

type Pos struct {
	Line int `json:"line"`
	Col  int `json:"col"`
	Idx  int `json:"idx"`
}

type T struct {
	Literal string `json:"literal"`
	Kind    Kind   `json:"kind"`
	Pos     Pos    `json:"pos"`
}
