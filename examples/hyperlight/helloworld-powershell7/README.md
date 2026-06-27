# PowerShell Script Example on Hyperlight

This example demonstrates running a PowerShell Core script within a Unikraft guest unikernel driven by the Hyperlight VMM.

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

Run the example with Kraft:
```bash
just run
```
Or manually:
```bash
kraft run --plat hyperlight --memory 1024Mi --rootfs hello-initrd.cpio .unikraft/build/powershell-hyperlight_hyperlight-x86_64 --as=kernel -- -NoProfile -File /scripts/hello.ps1
```
To run multiple times via Hyperlight snapshot/restore:
```bash
just run-10
```
Or manually:
```bash
kraft run --plat hyperlight --memory 1024Mi --rootfs hello-initrd.cpio --hyperlight-repeat 9 .unikraft/build/powershell-hyperlight_hyperlight-x86_64 --as=kernel -- -NoProfile -File /scripts/hello.ps1
```
