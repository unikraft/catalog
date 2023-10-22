# Unikraft Applications & Examples Catalog

This repository contains the official catalog of supported applications by
Unikraft.

In addition to supported applications, this repository contains templates and
examples of user-level programs built on top of runtimes that are available in
the catalog.

To get started using these pre-built Unikraft unikernel images, start by [installing the companion command-line toolchain `kraft`](https://unikraft.org/docs/cli):

```
curl --proto '=https' --tlsv1.2 -sSf https://get.kraftkit.sh | sh
```

You can view all the up-to-date images which are built in this repository directly in the CLI by running:

```
kraft pkg ls --apps --update
```

## Examples

| | Example |
|-|:-|
| ![](https://raw.githubusercontent.com/unikraft/catalog/main/icons/python3.svg) | [Simple Python 3.10 HTTP Web Server with `http.server.HTTPServer`](https://github.com/unikraft/catalog/tree/main/examples/http-python3.10) |

## Library

| Status | Image |
|-|-|
| ![](https://github.com/unikraft/catalog/actions/workflows/library-helloworld.yaml/badge.svg) | [`unikraft.org/helloworld:latest`](library/helloworld) |
| ![](https://github.com/unikraft/catalog/actions/workflows/library-nginx1.15.yaml/badge.svg) | [`unikraft.org/nginx:1.15`](library/nginx1.15) |
| ![](https://github.com/unikraft/catalog/actions/workflows/library-python3.10.yaml/badge.svg) | [`unikraft.org/python:3.10`](library/python3.10) |
| ![](https://github.com/unikraft/catalog/actions/workflows/library-redis7.0.yaml/badge.svg) | [`unikraft.org/redis:7.0`](library/redis7.0) |
