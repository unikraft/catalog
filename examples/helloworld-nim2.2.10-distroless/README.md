# Nim Hello World

This directory contains a minimal distroless Nim application running on Unikraft.

The application is compiled to a statically linked position-independent executable and placed into a `scratch` root filesystem.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to build and run the distroless image:

```bash
kraft run --rm --plat qemu --arch x86_64 -M 128M .
```

The Nim application prints:

```bash
Hello, World!
```

## Distroless Image

The application is compiled in a separate builder stage using the official Nim 2.2.10 image.

The final root filesystem is based on `scratch`:

```bash
FROM scratch

COPY --from=builder /out/hello /usr/bin/hello
```
The final filesystem contains only the compiled Nim executable.

It does not contain a Linux distribution, shell, package manager, Nim compiler, or other unnecessary userspace components.

## Build

The Nim application is compiled with release optimizations and linked statically as a position-independent executable:

```bash
nim c \
    -d:release \
    --passC:"-fPIE" \
    --passL:"-static -pie" \
    -o:/out/hello \
    main.nim
```

## Inspect and Close

To list information about the running Unikraft instance, use:

```bash
kraft ps
```

To close the Unikraft instance, close the kraft process with `Ctrl+c` or run:

```bash
kraft rm <instance-name>
```
## `kraft` and `sudo`


Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.

Read more about how to start `kraft` without `sudo` at:

https://unikraft.org/sudoless

## Learn More

- https://nim-lang.org/
- https://unikraft.org/docs/cli/running
- https://unikraft.org/guides/building-dockerfile-images-with-buildkit