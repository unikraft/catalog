FROM golang:1.21 as build

ARG VERSION=2.13.4

WORKDIR /go/src/github.com/mccutchen/go-httpbin

RUN --mount=type=cache,target=/root/go/pkg/mod \
    --mount=type=cache,target=/root/.cache/go-build \
    set -xe; \
    apt-get update; \
    apt-get install -y --no-install-recommends \
      git \
      ca-certificates; \
    git clone --depth=1 --branch v${VERSION} https://github.com/mccutchen/go-httpbin.git .; \
    mkdir -p dist; \
    CGO_ENABLED=1 go build \
    -buildmode=pie \
    -ldflags="-linkmode external -extldflags -static-pie" \
    -tags netgo\
    -o dist/go-httpbin ./cmd/go-httpbin

FROM scratch

COPY --from=build /go/src/github.com/mccutchen/go-httpbin/dist/go-httpbin /bin/
