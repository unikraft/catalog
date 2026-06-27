# Python Guest Networking Example on Hyperlight

This example demonstrates socket-based outbound and inbound networking (TCP/HTTPS/raw sockets) in a Python guest unikernel running on the Hyperlight VMM driver.

## Requirements

- `kraft` installed on your path.
- `hyperlight-unikraft` VMM installed on your path.

## How to Build

1. Build the kernel:
   ```bash
   just build
   ```
   Or manually:
   ```bash
   kraft build --plat hyperlight --arch x86_64
   ```

2. Build the rootfs (initrd):
   ```bash
   just rootfs
   ```
   *Note: Alternatively, KraftKit allows you to pass a `Dockerfile` path directly to the `rootfs`/`initrd` configuration or command-line flag (e.g., `--initrd Dockerfile`), and it will build and package the rootfs on the fly.*

## How to Run

1. Run HTTP GET socket test:
   ```bash
   just run-get
   ```
   Or manually:
   ```bash
   kraft run --plat hyperlight --memory 128Mi --rootfs initrd.cpio --hyperlight-net .unikraft/build/networking-py-hyperlight_hyperlight-x86_64 --as=kernel -- /http_get.py
   ```

2. Run High-Level HTTP GET (urllib) test:
   ```bash
   just run-urllib
   ```
   Or manually:
   ```bash
   kraft run --plat hyperlight --memory 128Mi --rootfs initrd.cpio --hyperlight-net .unikraft/build/networking-py-hyperlight_hyperlight-x86_64 --as=kernel -- /urllib_get.py
   ```

3. Run HTTPS (TLS) urllib test:
   ```bash
   just run-https
   ```
   Or manually:
   ```bash
   kraft run --plat hyperlight --memory 128Mi --rootfs initrd.cpio --hyperlight-net .unikraft/build/networking-py-hyperlight_hyperlight-x86_64 --as=kernel -- /https_test.py
   ```

4. Run TCP Echo Server (inbound listen):
   ```bash
   just run-echo
   ```
   Or manually:
   ```bash
   kraft run --plat hyperlight --memory 128Mi --rootfs initrd.cpio --port 8080:8080 .unikraft/build/networking-py-hyperlight_hyperlight-x86_64 --as=kernel -- /echo_server.py
   ```
