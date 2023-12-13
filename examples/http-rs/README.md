# Simple HTTP Rust Server on Unikraft

This directory contains a simple HTTP server written in Rust using [tiny-http](https://github.com/tiny-http/tiny-http) running with Unikraft.
The image opens up a simple HTTP server and provides a simple HTML response for each request.

To run this example, install [Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli) and [the `nightly` Rust toolchain channel through Rustup](https://www.rust-lang.org/tools/install).

Then, clone this repository and `cd` into this directory.
You can then build the project with:

```
KRAFTKIT_TARGET=http-rs cargo +nightly build -Z build-std=std,panic_abort --target x86_64-unikraft-linux-musl
```

In the above command, `KRAFTKIT_TARGET=http-rs` makes the name of the application known to `kraftld`.
Rust for Unikraft currently only supports the `qemu/x86_64` target.
If a `Kraftfile` contains more targets, the correct one can be selected through the `KRAFTKIT_PLAT` and `KRAFTKIT_ARCH` environment variables.

Once built, you can execute the unikernel via:

```
qemu-system-x86_64 \
    -display none -serial stdio \
    -nic user,hostfwd=::8080-:8080,model=virtio-net-pci \
    -kernel target/x86_64-unikraft-linux-musl/debug/http-rs
```

Once executed, query the simple HTTP server:

```console
curl localhost:8080
```

## Learn more

- [`*-unikraft-linux-musl`—The rustc book](https://doc.rust-lang.org/rustc/platform-support/unikraft-linux-musl.html)
- [The `Kraftfile` specification](https://unikraft.org/docs/cli/reference/kraftfile/latest)
