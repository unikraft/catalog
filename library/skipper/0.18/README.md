# Skipper 0.18

This directory contains the build definition for the `unikraft.org/skipper:0.18` image.

To run this image, first [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli).
After installation, you can start caddy by running the following:

```console
kraft run -M 512M -p 9090:9090 --plat qemu --arch x86_64 unikraft.org/skipper:0.18
```

To test the liveliness, query the server using:

```console
curl localhost:9090
```

You will get a `Hello, World!` message.


## Building from source

To build the image locally, clone this repository and `cd` into this directory.
Then run:

```console
kraft build .
```

To run the locally built image, use:

```console
kraft run -M 512M -p 9090:9090 .
```

## See also

- [How to run unikernels locally in Unikraft's Documentation](https://unikraft.org/docs/cli/running).
- [Skipper's documentation](https://opensource.zalando.com/skipper/)
