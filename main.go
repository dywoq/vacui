package main

import (
	"log"
	"voidmare/hub"
)

func main() {
	err := hub.Start()
	if err != nil {
		log.Println("Failed to start VOIDMARE: %v\n", err)
		return
	}
	defer hub.Shutdown()
}
