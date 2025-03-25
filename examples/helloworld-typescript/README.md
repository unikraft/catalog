# TypeScript Hello World on Unikraft

## Overview
A simple TypeScript "Hello World" example demonstrating Unikraft deployment.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Prerequisites
- Unikraft's `kraft` CLI tool
- Docker

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm --plat qemu --arch x86_64 -M 512M .
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.


## Additional Details
- Uses Node.js 20 Alpine base image
- Compiles TypeScript to JavaScript
- Minimal runtime footprint
```

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
- [WebSocket Protocol RFC6455](https://tools.ietf.org/html/rfc6455)