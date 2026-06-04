# POSIX C HostFS Example on Hyperlight

This example demonstrates using HostFS (preopened host directories mounted inside the guest) to perform standard POSIX file operations (such as open, read, write, stat, etc.) from a C application.

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
kraft run --plat hyperlight --memory 2Mi --rootfs hostfs-posix-c-initrd.cpio --hyperlight-mount ./work .unikraft/build/hostfs-posix-c-hyperlight_hyperlight-x86_64 --as=kernel
```
To run multiple times via Hyperlight snapshot/restore:
```bash
just run-10
```
Or manually:
```bash
kraft run --plat hyperlight --memory 2Mi --rootfs hostfs-posix-c-initrd.cpio --hyperlight-mount ./work --hyperlight-repeat 9 .unikraft/build/hostfs-posix-c-hyperlight_hyperlight-x86_64 --as=kernel
```
Example output:
```bash
[i] using arch=x86_64 plat=hyperlight
[+] building rootfs via file... done!                                                                                                x86_64 [2.3s]
hyperlight-unikraft v0.9.0
Kernel: ".unikraft/build/hostfs-posix-c-hyperlight_hyperlight-x86_64"
Initrd: ".unikraft/build/initramfs-x86_64.cpio"
Memory: 2097152 B, Stack: 8388608 B
Preopened: "./work" -> /host (guest)
hostfs-posix-c: unmodified POSIX against the sandboxed host mount
wrote /host/greeting.txt (83 bytes)
read (83 bytes):
---
Hello from Unikraft via transparent POSIX!
No hcall helpers — just open + write.
---
appended to /host/logs/app.log
stat: size=83
done.
[run 1/1] restore=71.1ms call=8.9ms
[timing] evolve=63.9ms total=143.9ms
```