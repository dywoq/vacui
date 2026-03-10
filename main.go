package main

import (
	"fmt"
	"strings"

	"github.com/dywoq/vacui/scanner"
	"github.com/dywoq/vacui/scanner/workers"
)

func main() {
	r := strings.NewReader("\"Hi!\"23")
	w := &workers.W{}

	s := scanner.New()
	s.UpdateR(r)
	w.Append(s)

	tokens, err := s.Do("foo.vac")
	if err != nil {
		panic(err)
	}

	for _, tok := range tokens {
		fmt.Printf("%s %s\n", tok.Lit, tok.Kind)
	}
}
