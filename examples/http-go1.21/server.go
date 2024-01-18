package main

import (
	"fmt"
	"net/http"
)

func hello(w http.ResponseWriter, req *http.Request) {
	fmt.Fprintf(w, "hello, world!\n")
}

func main() {
	http.HandleFunc("/", hello)
	fmt.Println("Listening on :8080...")
	http.ListenAndServe(":8080", nil)
}
