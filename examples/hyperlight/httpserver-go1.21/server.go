// Blocking HTTP server using raw syscalls for Hyperlight.
//
// Go's net/http uses accept4(2) with SOCK_NONBLOCK | SOCK_CLOEXEC, which
// Hyperlight's host-proxied socket layer doesn't support (returns EIO).
// This server calls accept(2) directly via SYS_ACCEPT and uses blocking
// I/O throughout, matching the pattern of the working Python echo_server.
//
// Routes (mirrors networking-python3.12/http_server.py):
//   GET  /    → HTML greeting page (browser)
//   HEAD /    → headers only
//   POST /wrk → JSON {"received_bytes": N} (wrk benchmark)
//   other     → 404 or 405 as appropriate

package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
	"syscall"
)

const (
	port    = 8080
	backlog = 128
	bufSize = 65536
)

var htmlGreeting = "<!doctype html>\n" +
	"<html lang=\"en\">\n" +
	"<head><meta charset=\"utf-8\"><title>Unikraft Hyperlight</title></head>\n" +
	"<body><h1>Hello from Unikraft on Hyperlight</h1></body>\n" +
	"</html>\n"

func main() {
	fd, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, 0)
	if err != nil {
		fmt.Fprintf(os.Stderr, "socket: %v\n", err)
		os.Exit(1)
	}
	defer syscall.Close(fd)

	syscall.SetsockoptInt(fd, syscall.SOL_SOCKET, syscall.SO_REUSEADDR, 1)

	sa := &syscall.SockaddrInet4{Port: port}
	if err := syscall.Bind(fd, sa); err != nil {
		fmt.Fprintf(os.Stderr, "bind: %v\n", err)
		os.Exit(1)
	}

	if err := syscall.Listen(fd, backlog); err != nil {
		fmt.Fprintf(os.Stderr, "listen: %v\n", err)
		os.Exit(1)
	}

	fmt.Printf("Serving on http://0.0.0.0:%d\n", port)

	for {
		connFd, err := blockingAccept(fd)
		if err != nil {
			fmt.Fprintf(os.Stderr, "accept: %v\n", err)
			continue
		}
		serve(connFd)
		syscall.Close(connFd)
	}
}

// blockingAccept calls SYS_ACCEPT directly, bypassing Go's syscall.Accept
// which tries accept4 first and only falls back on ENOSYS/EINVAL — not
// the EIO that Hyperlight returns.
func blockingAccept(listenFd int) (int, error) {
	r0, _, e1 := syscall.Syscall(
		syscall.SYS_ACCEPT,
		uintptr(listenFd),
		0, // NULL sockaddr
		0, // NULL addrlen
	)
	if e1 != 0 {
		return -1, e1
	}
	return int(r0), nil
}

// serve handles a single HTTP request on the given fd.
func serve(fd int) {
	buf := make([]byte, bufSize)
	n, err := syscall.Read(fd, buf)
	if err != nil || n == 0 {
		return
	}

	req := string(buf[:n])
	firstLine, rest, _ := strings.Cut(req, "\r\n")
	parts := strings.SplitN(firstLine, " ", 3)
	if len(parts) < 2 {
		sendResponse(fd, 400, "Bad Request", "text/plain", "bad request\n")
		return
	}

	method := parts[0]
	rawPath := parts[1]

	// Strip query string, keep only the path component
	path := rawPath
	if i := strings.IndexByte(path, '?'); i >= 0 {
		path = path[:i]
	}

	route(fd, method, path, rest)
}

func route(fd int, method, path, rawHeaders string) {
	switch path {
	case "/":
		routeRoot(fd, method)
	case "/wrk":
		routeWrk(fd, method, rawHeaders)
	default:
		sendResponse(fd, 404, "Not Found", "text/plain", "not found\n")
	}
}

// routeRoot serves the browser-facing HTML greeting.
func routeRoot(fd int, method string) {
	switch method {
	case "GET":
		sendResponse(fd, 200, "OK", "text/html; charset=utf-8", htmlGreeting)
	case "HEAD":
		sendResponse(fd, 200, "OK", "text/html; charset=utf-8", "")
	default:
		sendMethodNotAllowed(fd, "GET, HEAD")
	}
}

// routeWrk serves the wrk benchmark endpoint (POST only).
func routeWrk(fd int, method, rawHeaders string) {
	if method != "POST" {
		sendMethodNotAllowed(fd, "POST")
		return
	}

	contentLength := headerValue(rawHeaders, "Content-Length")
	bodyLen, err := strconv.Atoi(contentLength)
	if err != nil && contentLength != "" {
		sendResponse(fd, 400, "Bad Request", "application/json",
			"{\"error\":\"invalid content-length\"}\n")
		return
	}
	if bodyLen < 0 {
		bodyLen = 0
	}

	body := fmt.Sprintf("{\"received_bytes\":%d}\n", bodyLen)
	sendResponse(fd, 200, "OK", "application/json", body)
}

// headerValue extracts the first value for a case-insensitive header name
// from raw CRLF-delimited headers.
func headerValue(raw, name string) string {
	lower := strings.ToLower(name)
	for _, line := range strings.Split(raw, "\r\n") {
		if line == "" {
			break
		}
		k, v, ok := strings.Cut(line, ":")
		if ok && strings.ToLower(strings.TrimSpace(k)) == lower {
			return strings.TrimSpace(v)
		}
	}
	return ""
}

func sendResponse(fd, status int, statusText, contentType, body string) {
	resp := fmt.Sprintf(
		"HTTP/1.1 %d %s\r\n"+
			"Server: UnikraftHyperlightHTTP/1.0\r\n"+
			"Content-Type: %s\r\n"+
			"Content-Length: %d\r\n"+
			"Connection: close\r\n"+
			"\r\n%s",
		status, statusText, contentType, len(body), body,
	)
	syscall.Write(fd, []byte(resp))
}

func sendMethodNotAllowed(fd int, allow string) {
	resp := fmt.Sprintf(
		"HTTP/1.1 405 Method Not Allowed\r\n"+
			"Server: UnikraftHyperlightHTTP/1.0\r\n"+
			"Allow: %s\r\n"+
			"Content-Length: 0\r\n"+
			"Connection: close\r\n"+
			"\r\n",
		allow,
	)
	syscall.Write(fd, []byte(resp))
}
