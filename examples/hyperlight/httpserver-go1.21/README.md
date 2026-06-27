# Go HTTP Server Example on Hyperlight

This example demonstrates running a blocking Go 1.21 HTTP server on a Unikraft unikernel using the Hyperlight VMM driver. The server uses raw syscalls for accept/read/write to work around Hyperlight host-proxied socket limitations, and includes wrk and vegeta load-test helpers.

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
   kraft run --plat hyperlight --rm --memory 128Mi -p 8080:8080 .unikraft/build/httpserver-go-hyperlight-go1-21_hyperlight-x86_64 --as=kernel
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
Kernel: ".unikraft/build/httpserver-go-hyperlight-go1-21_hyperlight-x86_64"
Memory: 134217728 B, Stack: 8388608 B
Serving on http://0.0.0.0:8080
[run 1/1] restore=82.4ms call=73.8ms
[timing] evolve=149.3ms total=305.6ms
```