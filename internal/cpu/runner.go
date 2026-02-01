// Copyright 2026 dywoq
//
// This code is released under the Apache License 2.0:
// https://www.apache.org/licenses/LICENSE-2.0
//
// Repository:
// https://github.com/dywoq/vacui

package cpu

import (
	lua "github.com/yuin/gopher-lua"
)

// Runner represents the runner of .lua files
// in Vacui CPU environment.
type Runner struct {
	state    *lua.LState
	lazyInit bool
}

// RunFile runs a .lua file, specified in path.
// Returns an error if it failed to initialize, or run .lua file.
func (r *Runner) RunFile(path string) error {
	if !r.lazyInit {
		err := r.init()
		if err != nil {
			return err
		}
	}
	err := r.state.DoFile(path)
	if err != nil {
		return err
	}
	r.state.Close()
	return nil
}

func (r *Runner) init() error {
	r.state = lua.NewState(lua.Options{SkipOpenLibs: true})

	lua.OpenDebug(r.state)
	lua.OpenString(r.state)
	lua.OpenTable(r.state)
	lua.OpenMath(r.state)
	lua.OpenBase(r.state)
	lua.OpenPackage(r.state)

	r.state.PreloadModule("mymodule", func(L *lua.LState) int {
		mod := L.NewTable() // the module table

		// Add a function
		L.SetField(mod, "hello", L.NewFunction(func(L *lua.LState) int {
			name := L.ToString(1)
			L.Push(lua.LString("Hello, " + name))
			return 1
		}))

		// Add a constant
		L.SetField(mod, "pi", lua.LNumber(3.1415926))

		// Add a nested table
		nested := L.NewTable()
		L.SetField(nested, "version", lua.LString("1.0.0"))
		L.SetField(mod, "meta", nested)

		L.Push(mod) // push module table onto stack
		return 1    // one return value for require
	})

	r.lazyInit = true
	return nil
}
