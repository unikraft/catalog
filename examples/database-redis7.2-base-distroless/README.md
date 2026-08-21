# Redis - Distroless

This example demonstrates how to use [`Redis`](https://redis.io), an open-source in-memory storage, used as a distributed, in-memory key–value database, cache and message broker, with optional durability. It runs on Unikraft using the `gcr.io/distroless/cc-debian12` base image. This minimal environment lacks a shell and unnecessary system utilities, significantly reducing the attack surface.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -p 6379:6379 --plat qemu --arch x86_64 -M 256M .
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Then use `redis-cli` to test the connection:

```console
redis-cli set a 1
redis-cli get a
```

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME           KERNEL                          ARGS                                       CREATED        STATUS   MEM   PORTS                   PLAT
heuristic_moe  oci://unikraft.org/base:latest  /usr/bin/redis-server /etc/redis/redis...  5 seconds ago  running  244M  0.0.0.0:6379->6379/tcp  qemu/x86_64
```

The instance name is `heuristic_moe`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm heuristic_moe
```

Note that depending on how you modify this example your instance **may** need more memory to run.
To do so, use the `kraft run`'s `-M` flag, for example:

```bash
kraft run --rm -p 6379:6379 --plat qemu --arch x86_64 -M 512M .
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
