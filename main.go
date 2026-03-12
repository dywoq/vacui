package main

import (
	"encoding/json"
	"fmt"
	
	"os"
	

	"github.com/dywoq/vacui/parser"
	"github.com/dywoq/vacui/parser/workers"
	"github.com/dywoq/vacui/scanner"
	scanw "github.com/dywoq/vacui/scanner/workers"
)

func main() {
	f, err := os.Open("foo.vac")
	if err != nil {
panic(err)
	}

	w := &scanw.W{}

	s := scanner.New()
	s.UpdateR(f)
	w.Append(s)

	tokens, err := s.Do("foo.vac")
	if err != nil {
		panic(err)
	}

	for _, tok := range tokens {
		fmt.Printf("%s %s\n", tok.Lit, tok.Kind)
	}

	p := parser.New()
	p.Update(tokens)
	pw := workers.W{}
	pw.Append(p)

	body, err := p.Parse("foo.vac")
	if err != nil {
		panic(err)
	}

	for _, n := range body {
		bytes, _ := json.MarshalIndent(n, "", "   ")
		fmt.Printf("bytes: %v\n", string(bytes))
	}
}
