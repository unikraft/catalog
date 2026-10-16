# HTTP Response Cache

This directory contains a minimal HTTP response cache written in Rust and running on Unikraft.

The application stores generated HTTP responses in an in-memory cache and returns the cached response for subsequent requests to the same path.

The application is compiled into a statically linked executable and placed into a Distroless root filesystem.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Build and run the example with:

```bash
kraft run --rm --plat qemu --arch x86_64 -M 128M -p 8080:8080 .
```

The HTTP server listens on port `8080`.

The `-p 8080:8080` option forwards port `8080` from the Unikraft instance to port `8080` on the host.

### Test the Cache

Send a request to the application:

```bash
curl http://localhost:8080/hello
```

The first request to `/hello` produces a cache miss:

```text
CACHE MISS: Generated response for /hello
```

Send the same request again:

```bash
curl http://localhost:8080/hello
```

The subsequent request produces a cache hit:

```text
CACHE HIT: Generated response for /hello
```

Different paths are cached independently. For example:

```bash
curl http://localhost:8080/world
```

produces:

```text
CACHE MISS: Generated response for /world
```

A subsequent request to the same path returns:

```text
CACHE HIT: Generated response for /world
```

Only `GET` requests are supported. Other HTTP methods return `405 Method Not Allowed`.

For example:

```bash
curl -i -X POST http://localhost:8080/hello
```

returns:

```text
HTTP/1.1 405 Method Not Allowed
```

## Distroless Image

The application is compiled in a separate Rust builder stage.

The final root filesystem uses the Distroless static Debian 12 image:

```dockerfile
FROM gcr.io/distroless/static-debian12

COPY --from=builder /out/http-response-cache /usr/bin/http-response-cache
```

The final image contains the application executable together with the minimal files provided by the Distroless base image.

It does not contain a shell, package manager, Rust compiler, or other build-time tools.

## Build

The Rust application is compiled with release-oriented optimizations:

```bash
rustc \
    --edition=2021 \
    -C opt-level=3 \
    -C target-feature=+crt-static \
    -o /out/http-response-cache \
    main.rs
```

The Docker image can be built directly with:

```bash
docker build -t http-response-cache-distroless .
```

## Unikraft Build

To build the application image with Unikraft without starting it, run:

```bash
kraft build --plat qemu --arch x86_64 .
```

This builds the application root filesystem from the Dockerfile and prepares it to run as a Unikraft unikernel.

## Inspect and Close

To list information about the running Unikraft instance, use:

```bash
kraft ps
```

To close the Unikraft instance, press `Ctrl+c` in the terminal running `kraft run`.

Alternatively, a running instance can be removed with:

```bash
kraft rm <instance-name>
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.

Read more about how to start `kraft` without `sudo` at:

https://unikraft.org/sudoless

## Learn More

* https://www.rust-lang.org/
* https://unikraft.org/docs/cli/running
* https://unikraft.org/guides/building-dockerfile-images-with-buildkit
