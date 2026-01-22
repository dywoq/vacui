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
