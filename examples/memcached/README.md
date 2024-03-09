# Memcached

This examples demonstrates how to use [Memcached](https://memcached.org), n in-memory key-value store for small chunks of arbitrary data (strings, objects) from results of database calls, API calls, or page rendering.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -p 11211:11211 --plat qemu --arch x86_64 -M 256M .
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `11211:` and wait for connections.

To test it, run the following commands (you should see output when incrementing):

```console
telnet 127.0.0.1 11211
set test 0 0 1
0
incr test 1
incr test 1
```

To exit `telnet` use `Ctrl+]` in the `telnet` prompt.
The prompt will change to `telnet>`;
enter `quit`:

```console
telnet> quit
```

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME                 KERNEL                          ARGS        CREATED         STATUS   MEM   PLAT
admiring_ndakasi     oci://unikraft.org/base:latest  /server     1 minute ago    running  64MiB  0.0.0.0:8080->8080/tcp  qemu/x86_64
```

The instance name is `nostalgic_snowflake`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm nostalgic_snowflake
```

Note that depending on how you modify this example your instance **may** need more memory to run.
To do so, use the `kraft run`'s `-M` flag, for example:

```bash
kraft run --rm -p 11211:11211 --plat qemu --arch x86_64 -M 512M .
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
