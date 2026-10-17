FROM golang:1.22-alpine AS loki-build

WORKDIR /loki

# Dependencies
RUN set -xe; \
    apk --no-cache add \
      gcc \
      make \
      musl-dev \
      wget \
      git \
      linux-headers \
      upx \
      binutils \
    ; \
    update-ca-certificates;

# Build Loki as static PIE
RUN set -xe; \
    git clone https://github.com/grafana/loki.git .; \
    git checkout v2.9.8; \
    CGO_ENABLED=1 \
    go build -v \
      -buildmode=pie \
      -ldflags "-linkmode external -extldflags '-static-pie' -s -w" \
      -tags 'osusergo netgo static_build' \
      -trimpath \
      -o /usr/local/bin/loki \
      ./cmd/loki; \
    strip /usr/local/bin/loki; \
    upx --best --lzma /usr/local/bin/loki

FROM alpine:3 AS sys

RUN set -xe; \
    mkdir -p /target/etc; \
    mkdir -p /target/tmp/loki/chunks; \
    mkdir -p /target/tmp/loki/rules; \
    mkdir -p /target/etc/loki; \
    mkdir -p /blank; \
    apk --no-cache add \
      ca-certificates \
    ; \
    update-ca-certificates;

FROM scratch

COPY --from=sys /target/etc /etc
COPY --from=sys /etc/ssl/certs/ca-certificates.crt /etc/ssl/certs/ca-certificates.crt
COPY --from=sys /blank /tmp
COPY --from=sys /target/tmp /tmp

COPY --from=loki-build /usr/local/bin/loki /usr/local/bin/loki
COPY loki-local-config.yaml /etc/loki/loki-local-config.yaml
