package main

import (
	"log"
	"runtime"

	"github.com/pocketbase/pocketbase"
)

func main() {
	runtime.GOMAXPROCS(4)

	app := pocketbase.New()

	if err := app.Start(); err != nil {
		log.Fatal(err)
	}
}

