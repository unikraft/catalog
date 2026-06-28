package main

import (
	"fmt"
	"log"
	"net/http"
	"time"
)

func helloHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, "Hello from Hyperlight-Unikraft!")
}

func wrkHandler(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		w.Header().Set("Allow", "POST")
		http.Error(w, "Method Not Allowed", http.StatusMethodNotAllowed)
		return
	}

	bodyLen := int(r.ContentLength)
	if bodyLen < 0 {
		bodyLen = 0
	}

	w.Header().Set("Content-Type", "application/json")
	fmt.Fprintf(w, "{\"received_bytes\":%d}\n", bodyLen)
}

func main() {
	mux := http.NewServeMux()
	mux.HandleFunc("/", helloHandler)
	mux.HandleFunc("/wrk", wrkHandler)

	server := &http.Server{
		Addr:              ":8080",
		Handler:           mux,
		ReadHeaderTimeout: 5 * time.Second,
		IdleTimeout:       60 * time.Second,
	}

	fmt.Println("Server is running on http://localhost:8080")
	log.Fatal(server.ListenAndServe())
}
