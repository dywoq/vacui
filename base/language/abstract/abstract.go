package abstract

// Debugger represents the standard interface for the debuggers.
// The print functions work by default, but may behave differently if
// debugging mode is explicitly enabled in any structure that implements Debugger.
type Debugger interface {
	Debugf(format string, v ...any)
	Debugln(v ...any)
	Debug(v ...any)
}

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

// Advancer defines standard method for advancing to the next position
// or something similar.
type Advancer interface {
	Advance()
}
