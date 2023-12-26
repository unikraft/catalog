FROM golang:1.21.4-bookworm AS build

RUN set -xe; apt-get update ; \
    apt-get install -y --no-install-recommends \
      build-essential \
      git \
    ;

WORKDIR /

RUN set -xe; \
    wget -O skipper.tar.gz "https://github.com/zalando/skipper/archive/refs/tags/v0.18.51.tar.gz"; \
    tar xzvf skipper.tar.gz;

WORKDIR /skipper-0.18.51

RUN set -xe; \
    CGO_ENABLED=1 \
    go build \
        -buildmode=pie \
        -ldflags "-linkmode external -extldflags '-static-pie'" \
        -o /usr/bin/skipper \
        ./cmd/skipper

FROM scratch

COPY --from=build /usr/bin/skipper /usr/bin/skipper
COPY hello.eskip /etc/skipper/hello.eskip
