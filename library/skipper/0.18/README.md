# Skipper 0.18

This directory contains the definition for building the `unikraft.org/skipper:0.18` image.

To run this image, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli) and then you can run, as `root`:

```console
kraft net create -n 172.44.0.1/24 virbr0
kraft run -M 512M --network bridge:virbr0 --plat qemu --arch x86_64 unikraft.org/skipper:0.18
```

Query the server using:

```console
curl 172.44.0.2:9090
```

You will get a `Hello, World!` message.

## Build and Run Locally

To build the image locally, use:

```console
kraft build --no-cache --plat qemu --arch x86_64
```

To run the locally built image, use, as `root`:

```console
kraft net create -n 172.44.0.1/24 virbr0
kraft run -M 512M --network bridge:virbr0 --plat qemu --arch x86_64 .
```

## See also

- [How to run unikernels locally in Unikraft's Documentation](https://unikraft.org/docs/cli/running).
