# Shell Script Example on Hyperlight

This example demonstrates running a shell script (`demo.sh`) inside a shell interpreter unikernel using the Hyperlight VMM driver.

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
kraft run --plat hyperlight --memory 16Mi --rootfs initrd.cpio .unikraft/build/shell-hyperlight_hyperlight-x86_64 --as=kernel -- /demo.sh
```
To run multiple times via Hyperlight snapshot/restore:
```bash
just run-10
```
Or manually:
```bash
kraft run --plat hyperlight --memory 16Mi --rootfs initrd.cpio --hyperlight-repeat 9 .unikraft/build/shell-hyperlight_hyperlight-x86_64 --as=kernel -- /demo.sh
```
Example output:
```bash
[i] using arch=x86_64 plat=hyperlight
[+] building rootfs via file... done!                                                                                                x86_64 [2.9s]
hyperlight-unikraft v0.9.0
Kernel: ".unikraft/build/shell-hyperlight_hyperlight-x86_64"
Initrd: ".unikraft/build/initramfs-x86_64.cpio"
Memory: 16777216 B, Stack: 8388608 B
Hello from Shell on Hyperlight!

--- File operations ---
hyperlight
hello.txt

--- Text processing ---
charlie
1 /tmp/workspace/data.txt

--- Arithmetic ---
  42 + 13 = 55
  42 * 13 = 546

Done!
[run 1/1] restore=348.7ms call=17.2ms
[timing] evolve=656.0ms total=1022.0ms
```