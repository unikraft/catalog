# Python 3.12

This directory contains the definition for the `unikraft.org/python:3.12` image starting a simple HTTP server.

To run this image, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli) and then you can run:

```console
kraft run -p 8080:8080 -M 512M unikraft.org/python:3.12
```

Query the server using:

```console
curl localhost:8080
```

You will get a `Hello, World!` message.

## See also

- [How to run unikernels locally in Unikraft's Documentation](https://unikraft.org/docs/cli/running).
