# Skipper

[Skipper](https://opensource.zalando.com/skipper/) is an HTTP router and reverse proxy for service composition.
This example shows how to run it on Unikraft.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -p 9090:9090 --plat qemu --arch x86_64 -M 512M .
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `9090` and wait for connections.
To test it, you can use `curl`:

```bash
curl localhost:9090
```

You should see a "Hello, World!"-type message.

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME               KERNEL                           ARGS                                                      CREATED        STATUS   MEM   PORTS                   PLAT
unruffled_harambe  oci://unikraft.org/skipper:0.18  /usr/bin/skipper -routes-file /etc/skipper/example.eskip  3 seconds ago  running  0MiB  0.0.0.0:9090->9090/tcp  qemu/x86_64
```

The instance name is `unruffled_harambe`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm unruffled_harambe
```

Note that depending on how you modify this example your instance **may** need more memory to run.
To do so, use the `kraft run`'s `-M` flag, for example:

```bash
kraft run --rm -p 9090:9090 --plat qemu --arch x86_64 -M 1024M .
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
