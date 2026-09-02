# Rust HTTP Web Server - Distroless

This directory contains a [Rust](https://www.rust-lang.org/) HTTP server running on Unikraft.
It utilizes a Distroless container image (`gcr.io/distroless/cc-debian12`) to provide a minimal, secure root filesystem containing only the required runtime dependencies.

## Distroless Build

For this example's needs, the chosen distroless image provides:

- The dynamic linker `ld-linux-x86-64`
- The libraries `libc` and `libgcc_s`

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -p 8080:8080 --plat qemu --arch x86_64 -M 128M .
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `8080` and wait for connections.
To test it, you can use `curl`:

```bash
curl localhost:8080
```

You should see a "Bye, World!" message.

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME          KERNEL                          ARGS     CREATED         STATUS   MEM   PORTS                   PLAT
blissful_moe  oci://unikraft.org/base:latest  /server  19 seconds ago  running  128M  0.0.0.0:8080->8080/tcp  qemu/x86_64
```

The instance name is `blissful_moe`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm blissful_moe
```

Note that depending on how you modify this example your instance **may** need more memory to run.
To do so, use the `kraft run`'s `-M` flag, for example:

```bash
kraft run --rm -p 8080:8080 --plat qemu --arch x86_64 -M 256M .
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
