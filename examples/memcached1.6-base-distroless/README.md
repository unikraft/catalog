# Memcached 1.6 Distroless

This example demonstrates how to run [Memcached](https://memcached.org), an in-memory key-value store for small chunks of arbitrary data, on Unikraft using a minimal distroless root filesystem.

The root filesystem is built from `scratch` and contains only the Memcached binary, the required system libraries, certificates, timezone data, and configuration files needed to run the application.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -p 11211:11211 --plat qemu --arch x86_64 -M 256M .
```

If the `--plat` argument is left out, it defaults to `qemu`.

If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `11211` and wait for connections.

To test the Memcached server, use `nc`:

```bash
printf "set test 0 0 5\r\nhello\r\nget test\r\nquit\r\n" | nc 127.0.0.1 11211
```

You should see:

```text
STORED
VALUE test 0 5
hello
END
```

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

For example:

```text
NAME             KERNEL                            ARGS                        CREATED         STATUS   MEM   PORTS                     PLAT

admiring_pankun  oci://unikraft.org/memcached:1.6  /usr/bin/memcached -u root  54 seconds ago  running  244M  0.0.0.0:11211->11211/tcp  qemu/x86_64
```

The instance name is `admiring_pankun`.

To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm admiring_pankun
```

Note that depending on how you modify this example, your instance **may** need more memory to run.

To increase the allocated memory, use the `kraft run`'s `-M` flag, for example:

```bash
kraft run --rm -p 11211:11211 --plat qemu --arch x86_64 -M 512M .
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.

Read more about how to start `kraft` without `sudo` at https://unikraft.org/sudoless.

## Learn More

* [How to run unikernels locally](https://unikraft.org/docs/cli/running)
* [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
