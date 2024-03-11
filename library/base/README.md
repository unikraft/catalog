# Base Image

Base image is a Unikraft runtime built from [app-elfloader]() that loads and runs Linux native binaries using the [binary-compatibility mode](https://unikraft.org/docs/concepts/compatibility).

This directory contains the definition for the `unikraft.org/base:latest` image.

To run this image, [install Unikraft's companion command-line tool chain `kraft`](https://unikraft.org/docs/cli) and then you can run:

```
kraft run unikraft.org/base:latest
```
