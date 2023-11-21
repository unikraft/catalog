FROM golang:1.21.4-bookworm AS build

ARG SKIPPER_VERSION=0.18.51

RUN set -xe; apt-get update ; \
    apt-get install -y --no-install-recommends \
      build-essential \
      git \
    ;

WORKDIR /skipper

RUN set -xe; \
    wget -O skipper.tar.gz "https://github.com/zalando/skipper/archive/refs/tags/v${SKIPPER_VERSION}.tar.gz"; \
    tar -xzvf skipper.tar.gz --strip-components 1 -C /skipper;

RUN --mount=type=cache,target=/root/go/pkg/mod \
    --mount=type=cache,target=/root/.cache/go-build \
    set -xe; \
    CGO_ENABLED=1 \
    go build -v \
        -buildmode=pie \
        -ldflags "-linkmode external -extldflags '-static-pie'" \
        -o /usr/bin/skipper \
        ./cmd/skipper

FROM scratch

COPY --from=build /usr/bin/skipper /usr/bin/skipper
COPY hello.eskip /etc/skipper/hello.eskip
