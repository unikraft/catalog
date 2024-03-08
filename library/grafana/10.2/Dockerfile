FROM golang:1.21.4-alpine3.18 AS grafana-build

WORKDIR /grafana

# Dependencies
RUN set -xe; \
    apk --no-cache add \
      gcc \
      make \
      musl-dev \
      wget \
    ; \
    wget -O /grafana.tar.gz https://github.com/grafana/grafana/archive/refs/tags/v10.2.2.tar.gz; \
    tar -xzvf /grafana.tar.gz --strip-components 1 -C /grafana; \
    update-ca-certificates;

# Build backend
RUN set -xe; \
    make gen-go; \
    CGO_ENABLED=1 \
    go build -v \
      -buildmode=pie \
      -ldflags "-linkmode external -extldflags '-static-pie' -X 'main.version=10.2.2' -X 'main.commit=161e3ca' -X 'main.buildstamp=$(date)' -X 'main.buildBranch=main'" \
      -o /usr/share/grafana/bin/grafana \
      ./pkg/cmd/grafana

FROM grafana/grafana:10.2.2 AS grafana

FROM alpine:3 AS sys

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

COPY --from=sys /target/etc /etc
COPY --from=sys /usr/share/zoneinfo/Etc/UTC /usr/share/zoneinfo/Etc/UTC
COPY --from=sys /etc/ssl/certs/ca-certificates.crt /etc/ssl/certs/ca-certificates.crt
COPY --from=sys /blank /tmp

COPY --from=grafana-build /usr/share/grafana/bin/grafana /usr/share/grafana/bin/grafana
COPY --from=grafana       /usr/share/grafana/public/ /usr/share/grafana/public/
COPY --from=grafana       /usr/share/grafana/conf/ /usr/share/grafana/conf/
