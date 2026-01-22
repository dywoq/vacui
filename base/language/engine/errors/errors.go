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
