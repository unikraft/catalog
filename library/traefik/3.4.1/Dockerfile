FROM golang:1.25rc1-alpine3.22 AS builder

RUN set -xe; \
    apk --no-cache add \
      gcc \
      make \
      musl-dev \
      wget \
      bash \
      git \
    ; \
    git clone https://github.com/traefik/traefik.git;

RUN set -xe; \
    cd traefik; \
    git checkout tags/v3.4.1; \
    CGO_ENABLED=1 GOOS=linux GOARCH=amd64 go build \
        -ldflags "-s -w \
            -X github.com/traefik/traefik/v3/pkg/version.Version=3.4.1 \
            -X github.com/traefik/traefik/v3/pkg/version.Codename=cheddar \
            -X github.com/traefik/traefik/v3/pkg/version.BuildDate=$(date -u +%Y-%m-%d T%H:%M:%SZ)" \
        -buildmode=pie -linkshared -o /usr/bin/traefik ./cmd/traefik

FROM alpine:3.22 AS sys

RUN set -xe; \
    mkdir -p /target/etc; \
    mkdir -p /blank; \
    apk --no-cache add \
      ca-certificates \
      tzdata \
    ; \
    update-ca-certificates; \
    ln -sf ../usr/share/zoneinfo/Etc/UTC /target/etc/localtime; \
    echo "Etc/UTC" > /target/etc/timezone;

FROM scratch

COPY --from=builder /usr/bin/traefik /usr/bin/traefik
COPY --from=builder /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1

COPY --from=sys /target/etc /etc
COPY --from=sys /usr/share/zoneinfo/Etc/UTC /usr/share/zoneinfo/Etc/UTC
COPY --from=sys /etc/ssl/certs/ca-certificates.crt /etc/ssl/certs/ca-certificates.crt
COPY --from=sys /blank /tmp
COPY ./dynamic.yml /etc/traefik/dynamic.yml
COPY ./traefik.yml /etc/traefik/traefik.yml
