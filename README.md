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

You can view all the up-to-date images which are built from this repository directly in the CLI by running:

```
kraft pkg ls --apps --update
```

## Examples

| | Example |
|-|:-|
| ![](./.github/icons/c.svg) | [Simple "Hello, world!" application written in C](https://github.com/unikraft/catalog/tree/main/examples/helloworld-gcc13.2) |
| ![](./.github/icons/cpp.svg) | [Simple "Hello, world!" application written in C++](https://github.com/unikraft/catalog/tree/main/examples/helloworld-g++13.2) |
| ![](./.github/icons/rust-white.svg#gh-dark-mode-only)![](./.github/icons/rust-black.svg#gh-light-mode-only) | [Simple "Hello, world!" application written in Rust built via `cargo`](https://github.com/unikraft/catalog/tree/main/examples/helloworld-rust1.75) |
| ![](./.github/icons/js.svg) | [Simple NodeJS 18 HTTP Web Server with `http`](https://github.com/unikraft/catalog/tree/main/examples/httpserver-nodejs18-base) |
| ![](./.github/icons/go.svg) | [Simple Go 1.21 HTTP Web Server with `net/http`](https://github.com/unikraft/catalog/tree/main/examples/httpserver-go1.21) |
| ![](./.github/icons/python3.svg) | [Simple Flask 3.0 HTTP Web Server](https://github.com/unikraft/catalog/tree/main/examples/http-python3.10-flask3.0) |
| ![](./.github/icons/python3.svg) | [Simple Python 3.10 HTTP Web Server with `http.server.HTTPServer`](https://github.com/unikraft/catalog/tree/main/examples/httpserver-python3.10) |
| ![](./.github/icons/rust-white.svg#gh-dark-mode-only)![](./.github/icons/rust-black.svg#gh-light-mode-only) | [Rust Actix Web Server](https://github.com/unikraft/catalog/tree/main/examples/actix4-rust1.75) |
| ![](./.github/icons/rust-white.svg#gh-dark-mode-only)![](./.github/icons/rust-black.svg#gh-light-mode-only) | [Rust/Rocket v0.5](https://github.com/unikraft/catalog/tree/main/examples/rocket0.5-rust1.75) |
| ![](./.github/icons/rust-white.svg#gh-dark-mode-only)![](./.github/icons/rust-black.svg#gh-light-mode-only) | [Rust/Tokio Server](https://github.com/unikraft/catalog/tree/main/examples/tokio1-rust1.75) |
| ![](./.github/icons/rust-white.svg#gh-dark-mode-only)![](./.github/icons/rust-black.svg#gh-light-mode-only) | [Rust HTTP Web Server](https://github.com/unikraft/catalog/tree/main/examples/httpserver-rust1.75) |

## Library

| Status | Image |
|-|-|
| [![](https://github.com/unikraft/catalog/actions/workflows/library-base.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-base.yaml) | [`unikraft.org/base:latest`](library/base) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-bun1.1.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-bun1.1.yaml) | [`unikraft.org/bun:1.1`](library/bun/1.1) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-caddy2.7.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-caddy2.7.yaml) | [`unikraft.org/caddy:2.7`](library/caddy/2.7) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-dragonfly1.14.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-dragonfly1.14.yaml) | [`unikraft.org/dragonfly:1.14`](library/dragonfly/1.14) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-findtime.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-findtime.yaml) | [`unikraft.org/findtime`](library/findtime) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-grafana10.2.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-grafana10.2.yaml) | [`unikraft.org/grafana:10.2`](library/grafana/10.2) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-haproxy2.8.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-haproxy2.8.yaml) | [`unikraft.org/haproxy:2.8`](library/haproxy/2.8) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-helloworld.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-helloworld.yaml) | [`unikraft.org/helloworld:latest`](library/helloworld) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-httpbingo2.13.4.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-httpbingo2.13.4.yaml) | [`unikraft.org/httpbingo:2.13.4`](library/httpbingo/2.13.4) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-hugo0.122.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-hugo0.122.yaml) | [`unikraft.org/hugo:0.122`](library/hugo/0.122) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-imaginary1.2.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-imaginary1.2.yaml) | [`unikraft.org/imaginary:1.2`](library/imaginary/1.2) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-helloworld.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-helloworld.yaml) | [`unikraft.org/helloworld:latest`](library/helloworld) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-java17.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-java17.yaml) | [`unikraft.org/java:17`](library/java/17) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-lua5.4.4.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-lua5.4.4.yaml) | [`unikraft.org/lua:5.4.4`](library/lua/5.4.4) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-lua5.4.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-lua5.4.yaml) | [`unikraft.org/lua:5.4`](library/lua/5.4) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-mariadb11.2.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-mariadb11.2.yaml) | [`unikraft.org/mariadb:11.2`](library/mariadb/11.2) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-memcached1.6.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-memcached1.6.yaml) | [`unikraft.org/memcached:1.6`](library/memcached/1.6) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-mongo6.0.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-mongo6.0.yaml) | [`unikraft.org/mongo:6.0`](library/mongo/6.0) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-nats2.10.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-nats2.10.yaml) | [`unikraft.org/nats:2.10`](library/nats/2.10) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-nginx1.15.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-nginx1.15.yaml) | [`unikraft.org/nginx:1.15`](library/nginx/1.15) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-nginx1.25.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-nginx1.25.yaml) | [`unikraft.org/nginx:1.25`](library/nginx/1.25) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-node18.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-node18.yaml) | [`unikraft.org/node:18`](library/node/18) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-node20.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-node20.yaml) | [`unikraft.org/node:20`](library/node/20) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-node21.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-node21.yaml) | [`unikraft.org/node:21`](library/node/21) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-perl5.38.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-perl5.38.yaml) | [`unikraft.org/perl:5.38`](library/perl/5.38) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-php8.2.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-php8.2.yaml) | [`unikraft.org/php:8.2`](library/php/8.2) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-python3.10.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-python3.10.yaml) | [`unikraft.org/python:3.10`](library/python/3.10) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-python3.12.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-python3.12.yaml) | [`unikraft.org/python:3.12`](library/python/3.12) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-python3.13.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-python3.13.yaml) | [`unikraft.org/python:3.13`](library/python/3.13) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-redis7.0.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-redis7.0.yaml) | [`unikraft.org/redis:7.0`](library/redis/7.0) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-redis7.2.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-redis7.2.yaml) | [`unikraft.org/redis:7.2`](library/redis/7.2) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-ruby3.2.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-ruby3.2.yaml) | [`unikraft.org/ruby:3.2`](library/ruby/3.2) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-skipper0.18.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-skipper0.18.yaml) | [`unikraft.org/skipper:0.18`](library/skipper/0.18) |
| [![](https://github.com/unikraft/catalog/actions/workflows/library-surreal1.1.yaml/badge.svg)](https://github.com/unikraft/catalog/actions/workflows/library-surreal1.1.yaml) | [`unikraft.org/surreal:1.1`](library/surreal/1.1) |
