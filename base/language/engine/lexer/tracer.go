package lexer

import (
	"fmt"
	"io"
	"sync/atomic"
	"time"
)

// Tracer represents the standard lexer debugger.
// Implements [debug.Tracer] interface.
type Tracer struct {
	on atomic.Bool
	w  io.Writer
}

func (t *Tracer) Debugf(format string, v ...any) {
	if !t.on.Load() {
		return
	}
	userformat := fmt.Sprintf(format, v...)
	fmt.Fprintf(t.w, "-- %s Lexer: %s", time.Now().String(), userformat)
}

func (t *Tracer) Debugln(v ...any) {
	if !t.on.Load() {
		return
	}
	userformat := fmt.Sprintln(v...)
	fmt.Fprintf(t.w, "-- %s Lexer: %s", time.Now().String(), userformat)
}

func (t *Tracer) Debug(v ...any) {
	if !t.on.Load() {
		return
	}
	userformat := fmt.Sprint(v...)
	fmt.Fprintf(t.w, "-- %s Lexer: %s", time.Now().String(), userformat)
}
