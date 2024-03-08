# Bun

This directory contains the [Bun](https://bun.sh/) runtime on Unikraft, in binary compatibility mode.
It implements a simple server running on Unikraft that provides a simple response to each request.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -M 512M -p 3000:3000 --plat qemu --arch x86_64 unikraft.org/bun:1.1
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `3000` and wait for connections.
To test it, you can use `curl`:

```bash
curl localhost:3000
```

You should see a "Hello, World!" message.

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME            KERNEL                     ARGS                                 CREATED        STATUS   MEM   PORTS                   PLAT
eloquent_nyota  project://bun:qemu/x86_64  /usr/bin/bun run /usr/src/server.ts  8 seconds ago  running  0MiB  0.0.0.0:3000->3000/tcp  qemu/x86_64
```

The instance name is `eloquent_nyota`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm eloquent_nyota
```

## Build and Run Locally

The commands so far used the pre-build Bun image available in the Unikraft registry.

In oder to to build a local Bun image, clone this repository and `cd` into this directory.
Then use `kraft` to build an image locally:

```bash
kraft build --no-cache --no-update --plat qemu --arch x86_64
```

Similar to the `kraft run` command, if the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

In order to run the locally built image, use `.` (_dot_, the current directory)  as the final argument to the `kraft run` command:

```bash
kraft run --rm -M 512M -p 3000:3000 --plat qemu --arch x86_64 .
```

Same as above, it will open port `3000` and wait for connections.

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [How to build `Dockerfile` root filesystems with BuildKit](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
