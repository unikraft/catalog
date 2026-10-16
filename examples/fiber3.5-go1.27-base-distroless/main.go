package main

import (
	"runtime"
	"github.com/gofiber/fiber/v3"
)

func main() {
	runtime.GOMAXPROCS(4)

	app := fiber.New()

	app.Get("/", func(c fiber.Ctx) error {
		return c.SendString("Bye, World!\n")
	})

	app.Listen("0.0.0.0:8080")
}

