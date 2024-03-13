# Rust "Hello, World!"

This directory contains a Rust "Hello, World!" example running on Unikraft.

To run this example, install [Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli) and [the `nightly` Rust toolchain channel through Rustup](https://www.rust-lang.org/tools/install).

## Build

To build the image, clone this repository and `cd` into this directory.
You can then build the project with:

```bash
KRAFTKIT_TARGET=helloworld cargo +nightly build -Z build-std=std,panic_abort --target x86_64-unikraft-linux-musl
```

In the above command, `KRAFTKIT_TARGET=helloworld` makes the name of the application known to `kraftld`.
Rust for Unikraft currently only supports the `qemu/x86_64` target.
If a `Kraftfile` contains more targets, the correct one can be selected through the `KRAFTKIT_PLAT` and `KRAFTKIT_ARCH` environment variables.

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
- [`*-unikraft-linux-musl` - The `rustc` book](https://doc.rust-lang.org/rustc/platform-support/unikraft-linux-musl.html)
