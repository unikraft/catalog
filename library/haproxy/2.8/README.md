# HAProxy

This directory contains the [HAProxy](https://www.haproxy.org/) runtime on Unikraft, in binary compatibility mode.
It implements a simple HTTP server running on Unikraft that provides a simple response to each request.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -p 8404:8404 --plat qemu --arch x86_64 -M 256M unikraft.org/haproxy:2.8
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `8404` and wait for connections.
To test it, you can use `curl`:

```bash
curl localhost:8404/stats
```

You should see status information related to the HAProxy instance.

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME                    KERNEL                         ARGS                                           CREATED       STATUS   MEM   PORTS                   PLAT
agitated_pocketswarhol  project://haproxy:qemu/x86_64  /usr/bin/haproxy -f /etc/haproxy/haproxy.conf  1 minute ago  running  244M  0.0.0.0:8404->8404/tcp  qemu/x86_64
```

The instance name is `agitated_pocketswarhol`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm agitated_pocketswarhol
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
kraft run --rm -p 8404:8404 --plat qemu --arch x86_64 -M 256M .
```

Same as above, it will open port `8404` and wait for connections.

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [How to build `Dockerfile` root filesystems with BuildKit](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
