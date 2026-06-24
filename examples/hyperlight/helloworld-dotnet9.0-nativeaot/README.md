# .NET NativeAOT Hello World Example on Hyperlight

This example demonstrates running a .NET Hello World console application compiled using Native AOT (Ahead-Of-Time compilation) on a Unikraft unikernel using the Hyperlight VMM driver.

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
kraft run --plat hyperlight --memory 16Mi --rootfs hello-initrd.cpio .unikraft/build/dotnet-nativeaot-hyperlight_hyperlight-x86_64 --as=kernel
```
To run multiple times via Hyperlight snapshot/restore:
```bash
just run-10
```
Or manually:
```bash
kraft run --plat hyperlight --memory 16Mi --rootfs hello-initrd.cpio --hyperlight-repeat 9 .unikraft/build/dotnet-nativeaot-hyperlight_hyperlight-x86_64 --as=kernel
```
Example output:
```bash
[i] using arch=x86_64 plat=hyperlight
[+] building rootfs via file... done!                                                                                                x86_64 [2.3s]
hyperlight-unikraft v0.9.0
Kernel: ".unikraft/build/dotnet-nativeaot-hyperlight_hyperlight-x86_64"
Initrd: ".unikraft/build/initramfs-x86_64.cpio"
Memory: 16777216 B, Stack: 8388608 B
Hello, World! From .NET NativeAOT on Hyperlight!
[run 1/1] restore=85.6ms call=14.8ms
[timing] evolve=92.2ms total=192.6ms
```
