package debug

// Tracer represents the standard interface for the debuggers.
// The print functions work by default, but may behave differently if
// debugging mode is explicitly enabled in any structure that implements Debugger.
type Tracer interface {
	Debugf(format string, v ...any)
	Debugln(v ...any)
	Debug(v ...any)
}
