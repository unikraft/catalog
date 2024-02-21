FROM golang:1.21.3-bookworm AS build

ARG CADDY_VERSION=2.7.5

WORKDIR /caddy

RUN --mount=type=cache,target=/root/go/pkg/mod \
    --mount=type=cache,target=/root/.cache/go-build \
    set -xe; \
    apt-get update; \
    apt-get install -y --no-install-recommends \
      git \
      ca-certificates; \
    git clone --depth=1 --branch v${CADDY_VERSION} https://github.com/caddyserver/caddy.git /caddy; \
    go build -v \
      -buildmode=pie \
      -ldflags "-linkmode external -extldflags -static-pie" \
      -tags netgo \
      -o /caddy/caddy cmd/caddy/main.go;

RUN echo "127.0.0.1 localhost" > /tmp/hosts

FROM scratch

COPY --from=build /caddy/caddy /usr/bin/caddy
COPY --from=build /tmp/hosts /etc/hosts
COPY ./Caddyfile /etc/caddy/Caddyfile
