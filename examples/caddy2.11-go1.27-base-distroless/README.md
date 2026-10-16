# Go Caddy Web Server - Distroless

This directory contains a [`Caddy`](https://caddyserver.com/) web server running on Unikraft.
It utilizes a Distroless container image (`gcr.io/distroless/static-debian13`) to provide a minimal, secure root filesystem containing only the required runtime dependencies.

## Distroless Build

For this example's needs, the chosen distroless image provides:

- CA certificates (`ca-certificates`)
- Timezone data (`tzdata`)
- Standard `/tmp` and `/etc` directories

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -p 2015:2015 --plat qemu --arch x86_64 -M 512M .
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `2015` and wait for connections.
To test it, you can use `curl`:

```bash
curl localhost:2015
```

You should see a "Bye, World!" message.

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME                KERNEL                          ARGS                                      CREATED         STATUS   MEM   PORTS                   PLAT
affectionate_titus  oci://unikraft.org/base:latest  /usr/bin/caddy run --config /etc/cadd...  43 seconds ago  running  512M  0.0.0.0:2015->2015/tcp  qemu/x86_64
```

The instance name is `vigilant_michael`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm vigilant_michael
```

Note that depending on how you modify this example your instance **may** need more memory to run.
To do so, use the `kraft run`'s `-M` flag, for example:

```bash
kraft run --rm -p 2015:2015 --plat qemu --arch x86_64 -M 1G .
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
