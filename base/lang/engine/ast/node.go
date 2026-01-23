package ast

type Node interface {
	Node()
}

type Tree struct {
	Symbols string
	Nodes   []Node
}
