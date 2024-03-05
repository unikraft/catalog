# Memcached

This directory contains the [`Memcached`](https://memcached.org/) runtime on Unikraft, in binary compatibility mode.
It implements a simple HTTP server running on Unikraft that provides a simple response to each request.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -p 11211:11211 --plat qemu --arch x86_64 unikraft.org/memcached:1.6
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `11211` and wait for connections.

Investigate the service via `telnet`:

```console
telnet localhost 11211
```

```text
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
stats
STAT pid 1
STAT uptime 15
STAT time 1706423794
STAT version 1.6.23
STAT libevent 2.1.12-stable
STAT pointer_size 64
[...]
```

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME                    KERNEL                           ARGS                        CREATED        STATUS   MEM   PORTS                     PLAT
quizzical_johndanielii  project://memcached:qemu/x86_64  /usr/bin/memcached -u root  7 seconds ago  running  0MiB  0.0.0.0:11211->11211/tcp  qemu/x86_64
```

The instance name is `quizzical_johndanielii`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm quizzical_johndanielii
```

## Build and Run Locally

The commands so far used the pre-build Ruby image available in the Unikraft registry.

In oder to to build a local image, clone this repository and `cd` into this directory.
Then use `kraft` to build an image locally:

```bash
kraft build --no-cache --no-update --plat qemu --arch x86_64
```

Similar to the `kraft run` command, if the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

In order to run the locally built image, use `.` (_dot_, the current directory)  as the final argument to the `kraft run` command:

```bash
kraft run --rm -p 11211:11211 --plat qemu --arch x86_64 .
```

Same as above, it will open port `11211` and wait for connections.

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [How to build `Dockerfile` root filesystems with BuildKit](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
