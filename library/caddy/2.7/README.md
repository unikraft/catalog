# Caddy 2.7 Image

This directory contains the build definition for the `unikraft.org/caddy:2.7` image.

To run this image, first [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli).
After installation, you can start caddy by running the following:

```console
kraft run -M 512M -p 2015:2015 --plat qemu --arch x86_64 unikraft.org/caddy:2.7
```

To test the liveliness, query the server using:

```console
curl localhost:2015
```

You will get a `Hello, World!` message.


## Building from source

To build the image locally, clone this repository and `cd` into this directory.
Then run:

```console
kraft build --no-cache .
```

To run the locally built image, use:

```console
kraft run -M 512M -p 2015:2015 .
```

## See also

- [How to run unikernels locally in Unikraft's Documentation](https://unikraft.org/docs/cli/running).
- [Caddy's documentation](https://caddyserver.com/docs/)
