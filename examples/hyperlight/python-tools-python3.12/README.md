# Python Host Tools Dispatch Example on Hyperlight

This example demonstrates calling host-side functions (tools) from within a Python guest unikernel.
Tool dispatch is enabled via the `--hyperlight-enable-tools` flag, allowing the guest to invoke the `__dispatch` host function.

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
kraft run --plat hyperlight --memory 512Mi --rootfs initrd.cpio --hyperlight-enable-tools .unikraft/build/python-tools-hyperlight_hyperlight-x86_64 --as=kernel -- /test_tools.py
```
To run multiple times via Hyperlight snapshot/restore:
```bash
just run-10
```
Or manually:
```bash
kraft run --plat hyperlight --memory 512Mi --rootfs initrd.cpio --hyperlight-enable-tools --hyperlight-repeat 9 .unikraft/build/python-tools-hyperlight_hyperlight-x86_64 --as=kernel -- /test_tools.py
```
