# Go WebAssembly
FROM golang:1.27.0-trixie AS build-go

WORKDIR /build

COPY payloads/hello.go .

RUN set -xe; \
    GOOS=wasip1 GOARCH=wasm go build -o hello_go.wasm hello.go

# Rust WebAssembly
FROM rust:1.98-trixie AS build-rust

WORKDIR /build

RUN set -xe; \
    rustup target add wasm32-wasip1

COPY payloads/hello.rs .

RUN rustc --target wasm32-wasip1 hello.rs -o hello_rust.wasm

# C, C++, and Zig WebAssembly
FROM alpine:3.24 AS build-zig

WORKDIR /build

RUN apk add --no-cache zig

COPY payloads/hello.c payloads/hello.cpp payloads/hello.zig ./

RUN set -xe; \
    zig cc -target wasm32-wasi hello.c -o hello_c.wasm; \
    zig c++ -target wasm32-wasi hello.cpp -o hello_cpp.wasm; \
    zig build-exe hello.zig -target wasm32-wasi -O ReleaseSmall && mv hello.wasm hello_zig.wasm

# Wazero Host
FROM golang:1.27.0-trixie AS build-host

WORKDIR /app

COPY go.mod ./
COPY main.go .

RUN go mod tidy

RUN set -xe; \
    go build -v \
      -buildmode=pie \
      -ldflags="-linkmode external -extldflags -static-pie" \
      -tags netgo \
      -o runner main.go

FROM gcr.io/distroless/static-debian13@sha256:f2ea2709ac8db56323cbd7d014277f32cb572d9ea124b0076f7aafe5980678fe

# Host runner
COPY --from=build-host /app/runner /runner

# All WebAssembly payloads
COPY --from=build-go /build/hello_go.wasm /app/payloads/
COPY --from=build-rust /build/hello_rust.wasm /app/payloads/
COPY --from=build-zig /build/hello_c.wasm /app/payloads/
COPY --from=build-zig /build/hello_cpp.wasm /app/payloads/
COPY --from=build-zig /build/hello_zig.wasm /app/payloads/

