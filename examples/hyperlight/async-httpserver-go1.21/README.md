# Async Go HTTP Server Example on Hyperlight

This example demonstrates running an async Go 1.21 HTTP server on a Unikraft unikernel using the Hyperlight VMM driver. The server uses Go's standard `net/http` package, which handles concurrent requests with goroutines and therefore requires Hyperlight's host-proxied sockets to support `accept4(2)` (older builds return `EIO`; see [`httpserver-go1.21/server.go`](../httpserver-go1.21/server.go)). For a blocking, single-connection-at-a-time server built with raw syscalls, see [`httpserver-go1.21`](../httpserver-go1.21).

## Requirements

- `kraft` installed on your path.
- `hyperlight-unikraft` VMM installed on your path.

## How to Build

1. Build the kernel (embeds rootfs from Dockerfile):
   ```bash
   just build
   ```
   Or manually:
   ```bash
   kraft build --plat hyperlight --arch x86_64
   ```
   *Note: The `Kraftfile` points `rootfs` at `./Dockerfile`, so KraftKit builds and embeds the rootfs during `kraft build`.*

## How to Run

1. Run the HTTP server:
   ```bash
   just run
   ```
   Or manually:
   ```bash
   kraft run --plat hyperlight --rm --memory 128Mi -p 8080:8080 .unikraft/build/async-httpserver-go-hyperlight-go1-21_hyperlight-x86_64 --as=kernel
   ```

2. Run wrk load test (server must be running):
   ```bash
   just wrk
   ```

3. Run vegeta load test (server must be running):
   ```bash
   just vegeta
   ```

Example output:
```bash
[i] using arch=x86_64 plat=hyperlight
hyperlight-unikraft v0.9.0
Kernel: ".unikraft/build/async-httpserver-go-hyperlight-go1-21_hyperlight-x86_64"
Memory: 134217728 B, Stack: 8388608 B
Server is running on http://localhost:8080
[run 1/1] restore=82.4ms call=73.8ms
[timing] evolve=149.3ms total=305.6ms
```

## Benchmarks

Measured on Hyperlight with **128 MiB** guest memory, **4 wrk/vegeta threads**, and **64 concurrent connections** (wrk). All requests returned **HTTP 200**.

### wrk (30s sustained load)

| Endpoint | Requests | Throughput | Avg latency | Max latency |
|----------|----------|------------|-------------|-------------|
| `GET /` | 204,115 | **6,361 req/s** (0.90 MB/s) | 41.33 ms | 1.36 s |
| `POST /wrk` | 192,348 | **6,006 req/s** (762 KB/s) | 42.30 ms | 1.37 s |

`POST /wrk` used a 14-byte body (`hello from wrk`).

### vegeta (100 req/s, 10s)

| Endpoint | Requests | Success | Mean latency | p99 latency | Max latency |
|----------|----------|---------|--------------|-------------|-------------|
| `GET /` | 1,000 | 100% | 605 µs | 918 µs | 5.13 ms |
| `POST /wrk` | 1,000 | 100% | 617 µs | 917 µs | 2.48 ms |

`POST /wrk` used a 17-byte body (`hello from vegeta`).

### Summary

| Tool | Peak throughput | Sub-millisecond latency (vegeta) |
|------|-----------------|----------------------------------|
| wrk | ~6.4k req/s | — |
| vegeta | 100 req/s (saturated) | ~600 µs mean, <1 ms p99 |

Run the benchmarks yourself:

```bash
just run    # terminal 1
just wrk    # terminal 2
just vegeta # terminal 2
```
