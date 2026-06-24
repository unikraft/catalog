# Node.js Hello World Example on Hyperlight

This example demonstrates running a simple Node.js script in a Unikraft unikernel using the Hyperlight VMM driver.

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
kraft run --plat hyperlight --memory 512Mi --rootfs node-initrd.cpio .unikraft/build/nodejs-hyperlight_hyperlight-x86_64 --as=kernel -- /app/hello.js
```
To run multiple times via Hyperlight snapshot/restore:
```bash
just run-10
```
Or manually:
```bash
kraft run --plat hyperlight --memory 512Mi --rootfs node-initrd.cpio --hyperlight-repeat 9 .unikraft/build/nodejs-hyperlight_hyperlight-x86_64 --as=kernel -- /app/hello.js
```
Example output:
```bash
[i] using arch=x86_64 plat=hyperlight
[+] building rootfs via file... done!                                                                                                x86_64 [2.7s]
hyperlight-unikraft v0.9.0
Kernel: ".unikraft/build/nodejs-hyperlight_hyperlight-x86_64"
Initrd: ".unikraft/build/initramfs-x86_64.cpio"
Memory: 536870912 B, Stack: 8388608 B
Hello from Node.js on Hyperlight!
[run 1/1] restore=128.7ms call=171.3ms
[timing] evolve=3343.6ms total=3643.7ms
```