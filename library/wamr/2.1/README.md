# WARM

This directory contains the [WAMR (WebAssembly Micro Runtime)](https://github.com/bytecodealliance/wasm-micro-runtime) runtime on Unikraft, in binary compatibility mode.
It runs a "Hello, World!" web assembly program running on Unikraft.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -M 256M --plat qemu --arch x86_64 unikraft.org/wamr:2.1
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will print a "Hello, World!" message, from the `helloworld.c` source code file.

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME           KERNEL                      ARGS                                CREATED        STATUS   MEM   PORTS  PLAT
reverent_loon  project://wamr:qemu/x86_64  /usr/bin/iwasm /app/helloworld.aot  9 seconds ago  running  244M         qemu/x86_64
```

The instance name is `reverent_loon`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm reverent_loon
```

## Build and Run Locally

The commands so far used the pre-built WAMR image available in the Unikraft registry.

In oder to to build a local WAMR image, clone this repository and `cd` into this directory.
Then use `kraft` to build an image locally:

```bash
kraft build --no-cache --no-update --plat qemu --arch x86_64
```

Similar to the `kraft run` command, if the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

In order to run the locally built image, use `.` (_dot_, the current directory)  as the final argument to the `kraft run` command:

```bash
kraft run --rm -M 256M --plat qemu --arch x86_64 .
```

Same as above, it will print a "Hello, World!" message.

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [How to build `Dockerfile` root filesystems with BuildKit](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
