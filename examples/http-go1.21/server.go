package main

import (
	"fmt"
	"net/http"
)

func hello(w http.ResponseWriter, req *http.Request) {
	fmt.Fprintf(w, "Bye, World!\n")
}

func main() {
	http.HandleFunc("/", hello)
	fmt.Println("Listening on :8080...")
	http.ListenAndServe(":8080", nil)
}
