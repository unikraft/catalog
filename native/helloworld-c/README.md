# C "Hello, World!"

This directory contains a C-based "Hello, World!" example running on Unikraft.

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
kraft run --rm --plat qemu --arch x86_64 .
```

It will print out a "Hello, World!" message.

## Learn more

- [How to build unikernels](https://unikraft.org/docs/cli/building)
- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [The `Kraftfile` specification](https://unikraft.org/docs/cli/reference/kraftfile/latest)
