package errors

// ErrorMaker represents the standard methods of error making.
// It's purposed for structures that need different error formatting.
//
// External developers, relying on ErrorMaker, should write the plain messages only
// to not conflict with different formatting style of structure that implements ErrorMaker:
//
//	func err(e language.ErrorMaker) error {
//		return e.Error("something failed")
//	}
type ErrorMaker interface {
	Error(msg string) error
	Errorf(format string, v ...any) error
}
