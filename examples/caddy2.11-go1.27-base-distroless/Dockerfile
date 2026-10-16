FROM golang:1.27.0-trixie AS build

ARG CADDY_VERSION=2.11.4

WORKDIR /caddy

RUN --mount=type=cache,target=/root/go/pkg/mod \
    --mount=type=cache,target=/root/.cache/go-build \
    set -xe; \
    apt-get update; \
    apt-get install -y --no-install-recommends \
        git \
        ca-certificates; \
    git clone --depth=1 --branch v${CADDY_VERSION} https://github.com/caddyserver/caddy.git /caddy; \
    # Force patch not included in Caddy's go.mod file
    go get golang.org/x/net@v0.56.0; \
    go get golang.org/x/text@v0.39.0; \
    go get golang.org/x/crypto@v0.55.0; \
    go get google.golang.org/grpc@v1.83.2; \
    go mod tidy; \
    go build -v \
        -buildmode=pie \
        -ldflags "-linkmode external -extldflags -static-pie" \
        -tags netgo \
        -o /caddy/caddy cmd/caddy/main.go;

RUN echo "127.0.0.1 localhost" > /tmp/hosts

FROM gcr.io/distroless/static-debian13@sha256:f2ea2709ac8db56323cbd7d014277f32cb572d9ea124b0076f7aafe5980678fe

COPY --from=build /caddy/caddy /usr/bin/caddy
COPY --from=build /tmp/hosts /etc/hosts
COPY ./rootfs /

