# C "Hello, World!" - Distroless

This directory contains a C-based "Hello, World!" example running on Unikraft using the gcr.io/distroless/cc-debian12 base image. This minimal environment lacks a shell and unnecessary system utilities, significantly reducing the attack surface.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm --plat qemu --arch x86_64 -M 128M .
```

If the `--plat` argument is left out, it defaults to `qemu`.

If the `--arch` argument is left out, it defaults to your system's CPU architecture.

If the `-M` argument (memory allocation) is left out, it defaults to 64M. For this specific image,
leaving it out will cause a boot failure (cpio archive extraction error) because the virtual machine
runs out of memory while unpacking the filesystem in RAM. Explicitly setting it to -M 128M
provides enough memory and ensures the unikernel boots successfully.

Once executed, you should see a "Hello, World!" message.

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME              KERNEL                          ARGS         CREATED  STATUS   MEM   PORTS  PLAT
festive_albertii  oci://unikraft.org/base:latest  /helloworld  now      running  122M         qemu/x86_64
```

The instance name is `festive_albertii`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm festive_albertii
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
