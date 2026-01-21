package language

type TokenKind string

type TokenPosition struct {
	Line     int
	Column   int
	Position int
}

type Token struct {
	Literal  string
	Position TokenPosition
	Kind     TokenKind
}
