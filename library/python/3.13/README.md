# Python 3.13

This directory contains the definition for the `unikraft.org/python:3.13` image starting a simple HTTP server.

To run this image, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli) and then you can run:

```console
kraft run --rm -M 256M -p 8080:8080 unikraft.org/python:3.13
```

Query the server using:

```console
curl localhost:8080
```

You will get a `Hello, World!` message.

## See also

- [How to run unikernels locally in Unikraft's Documentation](https://unikraft.org/docs/cli/running).
