# Microbin

This directory contains the [Microbin](https://microbin.eu/) runtime on Unikraft, in binary compatibility mode.
It implements a super tiny, feature-rich, configurable, self-hosted pastebin application running on Unikraft.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -p 8080:8080 -v /tmp:/tmp --plat qemu --arch x86_64 -M 256M unikraft.org/microbin:2.0.4
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `8080` and wait for connections.
Open your web browser and navigate to:

```text
http://localhost:8080
```

You can now use the Microbin web interface to create and share pastes.

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps -a
```

```text
NAME         KERNEL                          ARGS        CREATED         STATUS   MEM   PORTS                   PLAT
kind_ozzie   project://microbin:qemu/x86_64  /microbin   15 seconds ago  running  256M  0.0.0.0:8080->8080/tcp  qemu/x86_64
```

The instance name is `kind_ozzie`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm kind_ozzie
```

## Build and Run Locally

The commands so far used the pre-built Microbin image available in the Unikraft registry.

In oder to to build a local Microbin image, clone this repository and `cd` into this directory.
Then use `kraft` to build an image locally:

```bash
kraft build --no-cache --no-update --plat qemu --arch x86_64
```

Similar to the `kraft run` command, if the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

In order to run the locally built image, use `.` (_dot_, the current directory)  as the final argument to the `kraft run` command:

```bash
kraft run --rm -p 8080:8080 -v /tmp:/tmp --plat qemu --arch x86_64 -M 256M .
```

Same as above, it will open port `8080` and wait for connections.

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [How to build `Dockerfile` root filesystems with BuildKit](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)