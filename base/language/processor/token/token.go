package token

type Kind string

type Position struct {
	Line     int
	Column   int
	Position int
}

type Token struct {
	Literal  string
	Position Position
	Kind     Kind
}
