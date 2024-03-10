# Simple C HTTP Server

This directory contains a simple C HTTP server running on Unikraft.

To use this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli).

## Build

To build the image, clone this repository and `cd` into this directory.
Then use `kraft` to build an image locally:

```bash
kraft build --no-cache --no-update --plat qemu --arch x86_64
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

## Run

In order to run the locally built image, use `kraft`:

```bash
kraft run --rm --plat qemu --arch x86_64 -p 8080:8080 .
```

Once executed, it will open port `8080` and wait for connections.
To test it, you can use `curl`:

```bash
curl localhost:8080
```

You should see a "Hello, World!" message.

## Learn more

- [How to build unikernels](https://unikraft.org/docs/cli/building)
- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [The `Kraftfile` specification](https://unikraft.org/docs/cli/reference/kraftfile/latest)
