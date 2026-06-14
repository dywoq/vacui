package main

import (
	"fmt"
	"strings"

	"github.com/dywoq/vacui/tools/vqbuild/config"
)

func main() {
	p := config.NewParser()
	r := strings.NewReader("# This is a comment!\nFOO = HI! \nXYZ = HI!")
	err := p.Read(r)
	if err != nil {
		panic(err)
	}
	
	keys, err := p.Parse()
	if err != nil {
		panic(err)
	}

	fmt.Printf("keys: %v\n", keys)
}
