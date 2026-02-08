// Copyright 2026 dywoq
//
// This code is released under Apache License 2.0:
// - https://www.apache.org/licenses/LICENSE-2.0
//
// The repository:
// - https://github.com/dywoq/vacui

// Package worker defines the standard behaviour for parse and scan workers.
//
// # Definition
//
// Worker - is a small, modular function, what's responsible turning input into output.
// It allows to easily scale language without changing the core structure (scanner/parser).
//
// # Input management
//
// To allow workers manage input and produce output, structures provide APIs.
// APIs must be minimal and provide only necessary methods to build helpers on top of them.
package worker
