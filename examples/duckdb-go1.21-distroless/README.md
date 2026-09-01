# DuckDB using Go SDK - Distroless

This example demonstrates how to use [`DuckDB`](https://duckdb.org), an in-process SQL OLAP database management system, in a Go project running on Unikraft with a minimal distroless root filesystem.

The application uses the [`go-duckdb`](https://github.com/marcboeker/go-duckdb) Go SDK to create a table, insert a record, query the database, and expose the result through an HTTP server.

The final root filesystem is built from `scratch`, containing only the application binary required to run the service.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

The source code and Go module files are located under the `src/` directory:

```text
duckdb-go1.21-distroless/
├── Dockerfile
├── Kraftfile
└── src/
    ├── go.mod
    ├── go.sum
    └── main.go
```

The `Dockerfile` uses a multi-stage build. The Go application is compiled using `golang:1.21.3-bookworm`, while the final stage uses `scratch` and contains only the resulting `/server` binary.

## Run and Use

Use `kraft` to build the distroless root filesystem and start a Unikraft instance:

```bash
kraft run --rm -p 8080:8080 --plat qemu --arch x86_64 -M 256M .
```

If the `--plat` argument is left out, it defaults to `qemu`.

If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, the application will start an HTTP server on port `8080`.

The application creates a DuckDB table, inserts the following record:

```text
id: 42
name: John
```

To test the HTTP server, use `curl`:

```bash
curl localhost:8080/
```

You should see:

```text
id: 42, name: John
```

## Distroless Root Filesystem

Unlike the original example, this variant does not include the Go build environment or a full Linux distribution in the final root filesystem.

The application is built in a separate stage and copied into a minimal `scratch` image:

```dockerfile
FROM golang:1.21.3-bookworm AS build

WORKDIR /src

COPY ./src/go.mod ./src/go.sum ./

RUN go mod download

COPY ./src/ ./

RUN CGO_ENABLED=1 go build \
    -buildmode=pie \
    -ldflags "-linkmode external -extldflags -static-pie" \
    -tags netgo \
    -o /server \
    .

FROM scratch

COPY --from=build /server /server
```

This keeps the final root filesystem minimal and removes unnecessary runtime components such as a shell, package manager, and other Debian userspace files.

## Inspect and Close

To list information about the running Unikraft instance, use:

```bash
kraft ps
```

For example:

```text
NAME        KERNEL                   ARGS     CREATED        STATUS   MEM   PORTS                   PLAT

sharp_jack  oci://unikraft.org/base:latest  /server  27 seconds ago  running  256M  0.0.0.0:8080->8080/tcp  qemu/x86_64
```

The instance name is `sharp_jack`.

To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm sharp_jack
```

Note that depending on how you modify this example, your instance may need more memory to run.

To increase the amount of memory available to the instance, use the `kraft run`'s `-M` flag:

```bash
kraft run --rm -p 8080:8080 --plat qemu --arch x86_64 -M 512M .
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.

Read more about how to start `kraft` without `sudo` at https://unikraft.org/sudoless.

## Learn More

* [How to run unikernels locally](https://unikraft.org/docs/cli/running)
* [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
* [DuckDB](https://duckdb.org)
* [go-duckdb](https://github.com/marcboeker/go-duckdb)
