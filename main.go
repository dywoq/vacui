package main

import (
	"fmt"
	"os"
	"voidmare/hub"
)

func main() {
	err := hub.Start()
	if err != nil {
		hub.PanicUI(fmt.Sprintf("Failed to start a game: %v", err))
		os.Exit(1)
	}
	defer hub.Shutdown()
}
