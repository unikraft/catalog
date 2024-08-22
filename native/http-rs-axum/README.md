# Rust HTTP Server with axum

This directory contains a simple HTTP server written in Rust using [axum](https://github.com/tokio-rs/axum) running with Unikraft.
The image opens up a simple HTTP server and provides a simple HTML response for each request.

To run this example, install [Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli) and the `nightly` Rust toolchain channel through [Rustup](https://www.rust-lang.org/tools/install).
To install the `nightly` Rust toolchain channel through Rustup, use:

```bash
rustup update nightly
rustup component add rust-src --toolchain nightly-x86_64-unknown-linux-gnu
```

## Build

To build the image, clone this repository and `cd` into this directory.
You can then build the project with:

```bash
KRAFTKIT_TARGET=http-rs-axum cargo +nightly build -Z build-std=std,panic_abort --target x86_64-unikraft-linux-musl
```

In the above command, `KRAFTKIT_TARGET=http-rs-axum` makes the name of the application known to `kraftld`.
Rust for Unikraft currently only supports the `qemu/x86_64` target.
If a `Kraftfile` contains more targets, the correct one can be selected through the `KRAFTKIT_PLAT` and `KRAFTKIT_ARCH` environment variables.

## Run

In order to run the locally built image, use `kraft`:

```bash
kraft run --rm --plat qemu --arch x86_64 -p 3000:3000 .
```

Once executed, it will open port `3000` and wait for connections.
To test it, you can use `curl`:

```bash
curl localhost:3000
```

You should see a "Hello, World!" message.

## Learn more

- [How to build unikernels](https://unikraft.org/docs/cli/building)
- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [The `Kraftfile` specification](https://unikraft.org/docs/cli/reference/kraftfile/latest)
- [`*-unikraft-linux-musl`—The `rustc` book](https://doc.rust-lang.org/rustc/platform-support/unikraft-linux-musl.html)
