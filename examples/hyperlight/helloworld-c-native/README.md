# C Hello World (Native) on Hyperlight

This example runs a C "Hello, World!" application on Hyperlight using the
**native-in-kernel** model: `helloworld.c` is compiled directly into the
Unikraft kernel via `Makefile.uk`. No ELF loader or initrd is required.

For the ELF-loader + initrd variant, see
[`helloworld-gcc13.2`](../helloworld-gcc13.2).

## Requirements

- `kraft` installed on your path
- `hyperlight-unikraft` VMM installed on your path (v0.9.0+)
- `/dev/kvm` access

## How to Build

Hyperlight:

```bash
just build
```

Or manually:

```bash
kraft build --plat hyperlight --arch x86_64
```

QEMU or Firecracker:

```bash
kraft build --plat qemu --arch x86_64
kraft build --plat fc --arch x86_64
```

## How to Run

Hyperlight:

```bash
just run
```

Or manually:

```bash
kraft run --plat hyperlight --memory 2Mi \
  .unikraft/build/helloworld-c-native_hyperlight-x86_64 --as=kernel
```

To run multiple times via Hyperlight snapshot/restore:

```bash
just run-10
```

QEMU or Firecracker:

```bash
kraft run --rm --plat qemu --arch x86_64 \
  .unikraft/build/helloworld-c-native_qemu-x86_64

kraft run --rm --plat fc --arch x86_64 \
  .unikraft/build/helloworld-c-native_fc-x86_64
```

Example output:

```bash
[i] using arch=x86_64 plat=hyperlight
hyperlight-unikraft v0.9.0
Kernel: ".unikraft/build/helloworld-c-native_hyperlight-x86_64"
Memory: 2097152 B, Stack: 8388608 B
[    0.000522] Warn: [apphelloworld] <helloworld.c @    6> Hello
[    0.002911] Warn: [apphelloworld] <helloworld.c @    7> .
Hello, World!
[run 1/1] restore=63.1ms call=1.0ms
[timing] evolve=48.5ms total=112.6ms
```

## Boot time comparison

`helloworld.c` prints `uk_pr_warn("Hello")` as the first action in `main()`.
With `CONFIG_LIBUKPRINT_PRINT_TIME=y`, the `[seconds.usec]` prefix is the
Unikraft monotonic time from kernel start to that line — i.e. guest boot time.

Build all targets, then measure:

```bash
just build-all
just boottime-hl
just boottime-qemu
just boottime-fc
```

All three use `kraft run --rm --as=kernel` for a consistent launch path.

Look at the timestamp on the `Hello` warn line. Run each several times and
average manually. Example results (5 runs each, WSL2/KVM):

| Platform | Avg boot to `main()` |
|----------|----------------------|
| Hyperlight | ~0.56 ms |
| Firecracker | ~106 ms |
| QEMU | ~121 ms |

The `[seconds.usec]` prefix is guest-side Unikraft monotonic time (VMM-independent).
Hyperlight also prints host-side `[timing] evolve=...` from the underlying VMM.