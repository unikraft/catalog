# POSIX Python HostFS Example on Hyperlight

This example demonstrates using HostFS (preopened host directories mounted inside the guest) to perform standard POSIX file operations using Python's filesystem APIs.

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
kraft run --plat hyperlight --memory 512Mi --rootfs hostfs-posix-py-initrd.cpio --hyperlight-mount ./work .unikraft/build/hostfs-posix-py-hyperlight_hyperlight-x86_64 --as=kernel -- /hostfs_demo.py
```
To run arbitrary Python code snippet:
```bash
just exec "print('hello from guest!')"
```
Or manually:
```bash
kraft run --plat hyperlight --memory 512Mi --rootfs hostfs-posix-py-initrd.cpio --hyperlight-exec "print('hello from guest!')" .unikraft/build/hostfs-posix-py-hyperlight_hyperlight-x86_64 --as=kernel
```
To run multiple times via Hyperlight snapshot/restore:
```bash
just run-10
```
Or manually:
```bash
kraft run --plat hyperlight --memory 512Mi --rootfs hostfs-posix-py-initrd.cpio --hyperlight-mount ./work --hyperlight-repeat 9 .unikraft/build/hostfs-posix-py-hyperlight_hyperlight-x86_64 --as=kernel -- /hostfs_demo.py
```
Example output:
```bash
[i] using arch=x86_64 plat=hyperlight
[+] building rootfs via file... done!                                                                                                x86_64 [2.5s]
hyperlight-unikraft v0.9.0
Kernel: "/home/jaidev/projects/open-source/kraftkit/examples/hostfs-posix-py/.unikraft/build/hostfs-posix-py-hyperlight_hyperlight-x86_64"
Initrd: ".unikraft/build/initramfs-x86_64.cpio"
Memory: 536870912 B, Stack: 8388608 B
Preopened: "/home/jaidev/projects/open-source/kraftkit/examples/hostfs-posix-py/work" -> /host (guest)
hostfs-posix-py: unmodified Python stdlib against the sandboxed host mount
wrote /host/greeting.txt (94 chars)
read /host/greeting.txt (94 chars):
---
Hello from Unikraft via transparent POSIX (Python)!
Just open() and write() — no SDK imports.
---
appended to /host/logs/app.log
stat /host/greeting.txt: size=96
after truncate(5): size=5
content: 'Hello'
done.
[run 1/1] restore=171.8ms call=80.2ms
[timing] evolve=2852.4ms total=3104.5ms
```