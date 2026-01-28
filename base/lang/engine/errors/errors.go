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

package errors

// Maker represents the standard methods of error making.
// It's purposed for structures that need different error formatting.
//
// External developers, relying on Maker, should write the plain messages only
// to not conflict with different formatting style of structure that implements Maker:
//
//	func err(e errors.Maker) error {
//		return e.Error("something failed")
//	}
type Maker interface {
	Error(msg string) error
	Errorf(format string, v ...any) error
}
