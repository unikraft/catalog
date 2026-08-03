# Rust 1.75 HTTP Server on Hyperlight (Base Runtime)

This directory contains a Rust 1.75 HTTP server example running on Unikraft using the Hyperlight VMM driver and base runtime (`base:latest`).

## Requirements

- `kraft` installed on your path.
- `hyperlight-unikraft` VMM installed on your path.

## How to Build and Run

1. Build the rootfs:

```bash
kraft build --rootfs ./Dockerfile --plat hyperlight --arch x86_64
```

Or using `just`:

```bash
just build
```

2. Run the HTTP server using `kraft`:

```bash
kraft run --plat hyperlight --rootfs .unikraft/build/initramfs-x86_64.cpio -p 8080:8080 .
```

Or using `just`:

```bash
just run
```

Once executed, port `8080` will be open. You can test it with `curl`:

```bash
curl http://localhost:8080
```

You should see:

```html
<html><body><h1>Hello from Rust on Hyperlight!</h1></body></html>
```
