# Python 3.13

This directory contains the definition for the `unikraft.org/python:3.13` image starting a simple HTTP server.


To use this application, first [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli).

You can run the pre-build image directly from the Unikraft application registry:

```console
kraft run --rm -M 256M -p 8080:8080 unikraft.org/python:3.13
```

Or you can build the application image (with Unikraft):

```console
rm -fr .config* .unikraft ; kraft build --no-cache --no-update --plat qemu --arch x86_64 .
```

And run the local image:

```console
kraft run --rm -p 8080:8080 --plat qemu --arch x86_64 -M 512M .
```

Then, query the server using:

```console
curl localhost:8080
```

You will get a `Hello, World!` message.

## See also

- [How to run unikernels locally in Unikraft's Documentation](https://unikraft.org/docs/cli/running).
