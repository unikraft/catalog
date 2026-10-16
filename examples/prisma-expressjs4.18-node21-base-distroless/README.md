# Node.js 21 Prisma Server - Distroless

This directory contains a Node.js 21 [`Prisma`](https://www.prisma.io/) implementation running on Unikraft using the `cgr.dev/chainguard/node` distroless base image.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -p 3000:3000 --plat qemu --arch x86_64 -M 1024M .
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.
If the `-M` argument (memory allocation) is left out, it defaults to 64M. For this specific image, leaving it out will cause a boot failure (e.g., `Resource exhaustion`) because the virtual machine requires more memory to load the Node.js runtime and the Prisma Query Engine. Explicitly setting it to `-M 1024M` provides enough memory and ensures the unikernel boots successfully.

Once executed, it will open port `3000` and wait for connections.
To test it, you can use `curl`:

```bash
curl localhost:3000/feed
```

You should see a feed of blog posts in JSON format.

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME             KERNEL                          ARGS                                CREATED         STATUS   MEM   PORTS                   PLAT
quizzical_zhong  oci://unikraft.org/base:latest  /usr/bin/node /usr/src/server.js    15 seconds ago  running  976M  0.0.0.0:3000->3000/tcp  qemu/x86_64
```

The instance name is `quizzical_zhong`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm quizzical_zhong
```

Note that depending on how you modify this example your instance **may** need more memory to run.
To do so, use the `kraft run`'s `-M` flag, for example:

```bash
kraft run -p 3000:3000 --plat qemu --arch x86_64 -M 2048M -e PRISMA_TELEMETRY_OPT_OUT=1 -e PRISMA_HIDE_UPDATE_MESSAGE=1 .
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
