// Copyright 2026 dywoq
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

func (t *Tracer) SetMode(on bool) {
	t.on.Store(on)
}

func (t *Tracer) On() bool {
	return t.on.Load()
}

func (t *Tracer) SetWriter(w io.Writer) {
	t.w = w
}

func (t *Tracer) Writer() io.Writer {
	return t.w
}
