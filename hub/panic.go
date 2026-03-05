package hub

import (
	"fmt"
	"os"
	"sync/atomic"

	"github.com/gen2brain/beeep"
)

var (
	panicOn atomic.Bool
)

// PanicOn returns true if the game hub panicked.
func PanicOn() bool {
	return panicOn.Load()
}

// TODO:
//
// After localization is supported, we should load panic message/app name
// from one of localization configurations. Both in PanicUI and Panic.

// PanicUI alerts the user about panic through UI.
// If it fails, it outputs a panic message into the console automatically.
//
// Returns if the hub already panicked.
func PanicUI(msg string) {
	if panicOn.Load() {
		return
	}
	beeep.AppName = "VOIDMARE"
	err := beeep.Alert("Hub just panicked!", msg, "")
	if err != nil {
		Panic(msg)
		return
	}
	panicOn.Store(true)
}

// Panic prints a panic message into the console,
// setting the panic mode to true.
//
// Returns if the hub already panicked.
func Panic(msg string) {
	if panicOn.Load() {
		return
	}
	fmt.Fprintf(os.Stderr, "voidmare: panic: %s\n", msg)
	panicOn.Store(true)
}
