# Go Wazero Polyglot - Distroless

This directory contains a Go [Wazero](https://wazero.io/) runtime example running on Unikraft, which sequentially executes 5 distinct WASI (WebAssembly System Interface) payloads written in C, C++, Go, Rust, and Zig.
It utilizes a Distroless container image (`gcr.io/distroless/static-debian13`) to provide a minimal, secure root filesystem containing only the required runtime dependencies.

## Distroless Build

For this example's needs, the chosen distroless image provides a completely bare filesystem.

Because the Wazero host runner is compiled as a statically linked PIE, it does not require `libc` or a dynamic linker.
The multi-stage Docker build handles the compilation of all 5 languages into `.wasm` files and drops them alongside the static Go `/runner` binary.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm --plat qemu --arch x86_64 -M 256M .
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

You should see Wazero iterate through the directory and output:

```text
Bye, World, from C!
Bye, World, from C++!
Bye, World, from Go!
Bye, World, from Rust!
Bye, World, from Zig!
```

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME          KERNEL                          ARGS         CREATED        STATUS   MEM  PORTS  PLAT
juicy_goblin  oci://unikraft.org/base:latest  /runner      9 seconds ago  running  256M        qemu/x86_64
```

The instance name is `juicy_goblin`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm juicy_goblin
```

Note that depending on how you modify this example your instance **may** need more memory to run.
To do so, use the `kraft run`'s `-M` flag, for example:

```bash
kraft run --rm --plat qemu --arch x86_64 -M 512M .
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
