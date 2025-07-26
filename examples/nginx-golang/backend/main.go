package main

import (
	"fmt"
	"log"
	"net/http"

	"github.com/go-chi/chi/v5"
	"github.com/go-chi/chi/v5/middleware"
)

func handler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(
		w, `
 .--------------------.
( Hello from Unikraft! )
 '--------------------'
         \\
          \\
             _
           c'o'o  .--.
           (| |)_/

`,
	)
}

func main() {
	r := chi.NewRouter()
	r.Use(middleware.Logger)
	r.Get("/", handler)

	fmt.Println("Go backend started!")
	log.Fatal(http.ListenAndServe(":80", r))
}
