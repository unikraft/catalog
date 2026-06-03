# Python Script Example on Hyperlight

This example demonstrates running a basic Python script inside a Unikraft unikernel using the Hyperlight VMM driver.

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
kraft run --plat hyperlight --memory 512Mi --rootfs initrd.cpio .unikraft/build/python-hyperlight_hyperlight-x86_64 --as=kernel -- /hello.py
```
To run multiple times via Hyperlight snapshot/restore:
```bash
just run-10
```
Or manually:
```bash
kraft run --plat hyperlight --memory 512Mi --rootfs initrd.cpio --hyperlight-repeat 9 .unikraft/build/python-hyperlight_hyperlight-x86_64 --as=kernel -- /hello.py
```
Example output:
```bash
[i] using arch=x86_64 plat=hyperlight
[+] building rootfs via file... done!                                                                                                x86_64 [2.4s]
hyperlight-unikraft v0.9.0
Kernel: ".unikraft/build/python-hyperlight_hyperlight-x86_64"
Initrd: ".unikraft/build/initramfs-x86_64.cpio"
Memory: 536870912 B, Stack: 8388608 B
Hello from Python on Hyperlight!
[run 1/1] restore=172.5ms call=69.9ms
[timing] evolve=2105.6ms total=2348.0ms
```