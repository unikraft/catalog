# Findtime

This directory contains the [Findtime](https://github.com/fbergen/findtime) application running on Unikraft, in binary compatibility mode.
It implements a simple HTTP-like server that you can use go aggregate multiple appointment links.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -M 256M -p 8080:8080 --plat qemu --arch x86_64 unikraft.org/findtime
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `8080` and wait for connections.
To test it, open a browser and then query a catalog entry such as

```bash
curl localhost:8080/?q=awesome_travis
```

You would get a web-based calendar with collected entries filled in.

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME             KERNEL                          ARGS       CREATED        STATUS   MEM   PORTS                   PLAT
priceless_flirt  project://findtime:qemu/x86_64  /findtime  5 seconds ago  running  244M  0.0.0.0:8080->8080/tcp  qemu/x86_64
```

The instance name is `priceless_flirt`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm awesome_travis
```

## Build and Run Locally

The commands so far used the pre-build Findtime image available in the Unikraft registry.

In oder to to build a local Findtime image, clone this repository and `cd` into this directory.
Then use `kraft` to build an image locally:

```bash
kraft build --no-cache --no-update --plat qemu --arch x86_64
```

Similar to the `kraft run` command, if the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

In order to run the locally built image, use `.` (_dot_, the current directory)  as the final argument to the `kraft run` command:

```bash
kraft run --rm -M 256M -p 8080:8080 --plat qemu --arch x86_64 .
```

Same as above, it will open port `8080` and wait for connections.

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [How to build `Dockerfile` root filesystems with BuildKit](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
