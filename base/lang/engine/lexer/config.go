package lexer

import (
	"github.com/dywoq/vacui/base/lang/engine/debug"
	"github.com/dywoq/vacui/base/lang/engine/errors"
)

// Config represents the lexer configuration.
type Config struct {
	DebugTracer debug.Tracer
	ErrorsMaker errors.Maker
	Context     Context
}
