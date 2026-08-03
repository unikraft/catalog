# Zig 0.11 Hello World on Hyperlight (Base Runtime)

This directory contains a Zig 0.11 Hello World example running on Unikraft using the Hyperlight VMM driver and base runtime (`base:latest`).

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

2. Run using `kraft`:

```bash
kraft run --plat hyperlight --rootfs .unikraft/build/initramfs-x86_64.cpio .
```

Or using `just`:

```bash
just run
```

You should see output:

```
Hello from Zig on Hyperlight!
```
