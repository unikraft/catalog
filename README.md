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
| ![](https://raw.githubusercontent.com/unikraft/catalog/main/icons/c.svg) | [Simple "Hello, world!" application written in C](https://github.com/unikraft/catalog/tree/main/examples/helloworld-c) |
| ![](https://raw.githubusercontent.com/unikraft/catalog/main/icons/cpp.svg) | [Simple "Hello, world!" application written in C++](https://github.com/unikraft/catalog/tree/main/examples/helloworld-cpp) |
| ![](https://raw.githubusercontent.com/unikraft/catalog/main/icons/python3.svg) | [Simple Flask 3.0 HTTP Web Server](https://github.com/unikraft/catalog/tree/main/examples/http-python3.10-flask3.0) |
| ![](https://raw.githubusercontent.com/unikraft/catalog/main/icons/python3.svg) | [Simple Python 3.10 HTTP Web Server with `http.server.HTTPServer`](https://github.com/unikraft/catalog/tree/main/examples/http-python3.10) |

## Library

| Status | Image |
|-|-|
| [![](https://github.com/unikraft/catalog/actions/workflows/library-base.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-base.yaml) | [`unikraft.org/base:latest`](library/base) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-helloworld.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-helloworld.yaml) | [`unikraft.org/helloworld:latest`](library/helloworld) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-nginx1.15.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-nginx1.15.yaml) | [`unikraft.org/nginx:1.15`](library/nginx/1.15) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-python3.10.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-python3.10.yaml) | [`unikraft.org/python:3.10`](library/python/3.10) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-redis7.0.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-redis7.0.yaml) | [`unikraft.org/redis:7.0`](library/redis/7.0) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-lua5.4.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-lua5.4.yaml) | [`unikraft.org/lua:5.4`](library/lua/5.4) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-node18.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-node18.yaml) | [`unikraft.org/node:18`](library/node/18) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-skipper0.18.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-skipper0.18.yaml) | [`unikraft.org/skipper:0.18`](library/skipper/0.18) |
