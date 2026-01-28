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

package scan

// Advancer defines standard method for advancing to the next position
// or something similar.
type Advancer interface {
	Advance()
}

// Backwards defines standard method for advancing backwards to the previous position
// or something similar.
type Backwards interface {
	Backwards()
}

// Slicer defines standard method for slicing input between start and end.
type Slicer interface {
	Slice(start, end int) (string, error)
}

// EofChecker defines method for checking EOF (End Of File).
type EofChecker interface {
	Eof() bool
}

// SofChecker defines method for checking SOF (Start Of File).
type SofChecker interface {
	Sof() bool
}
