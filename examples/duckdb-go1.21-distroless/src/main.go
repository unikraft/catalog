package main

import (
	"database/sql"
	"fmt"
	"net/http"

	_ "github.com/marcboeker/go-duckdb"
)

func main() {
	db, _ := sql.Open("duckdb", "")

	db.Exec(`CREATE TABLE person (id INTEGER, name VARCHAR)`)
	db.Exec(`INSERT INTO person VALUES (42, 'John')`)

	var (
		id   int
		name string
	)
	row := db.QueryRow(`SELECT id, name FROM person`)
	_ = row.Scan(&id, &name)
	fmt.Println("id:", id, "name:", name)

	// Serve the print on port 8080 as a http server
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprintln(w, "id: %d, name: %s", id, name)
	})
	http.ListenAndServe(":8080", nil)
}
