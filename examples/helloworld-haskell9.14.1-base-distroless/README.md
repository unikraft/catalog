# Haskell 9.14.1 "Bye, World!" - Distroless

This directory contains a Haskell-based "Bye, World!" example running on Unikraft using the `gcr.io/distroless/cc-debian12` base image. This specific image provides a minimal runtime environment optimized for dynamically linked applications. To ensure compatibility with Unikraft's POSIX implementation, a minimal C shim is linked to intercept unsupported `clock_gettime` calls made by the Haskell Runtime System (RTS). The final image contains only the necessary dependencies (like `libgmp` and `libffi`), completely stripping away the shell and unnecessary system utilities to reduce the attack surface.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm --plat qemu --arch x86_64 -M 256M .
```

If the `--plat` argument is left out, it defaults to `qemu`.

If the `--arch` argument is left out, it defaults to your system's CPU architecture.

If the `-M` argument (memory allocation) is left out, it defaults to 64M. For this specific image, leaving it out will cause a boot failure (cpio archive extraction error) because the virtual machine runs out of memory while unpacking the filesystem in RAM. Explicitly setting it to `-M 256M` provides enough memory and ensures the unikernel boots successfully.

Once executed, you should see a "Bye, World!" message.

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME            KERNEL                          ARGS       CREATED  STATUS   MEM   PORTS  PLAT
hungry_kokomo   oci://unikraft.org/base:latest  /app/Main  now      running  244M         qemu/x86_64
```

The instance name is `hungry_kokomo`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm hungry_kokomo
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
