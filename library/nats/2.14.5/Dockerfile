FROM golang:1.25-alpine AS build

WORKDIR /src
ADD https://github.com/nats-io/nats-server/archive/refs/tags/v2.14.5.tar.gz /src.tar.gz

RUN tar -xzf /src.tar.gz --strip-components=1 && \
    CGO_ENABLED=0 go build -trimpath -buildmode=pie -ldflags "-s -w" \
      -o /usr/bin/nats-server .

FROM nats:2.14.5-alpine AS conf

FROM scratch

COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=build /usr/bin/nats-server /usr/bin/nats-server
COPY --from=conf /etc/nats/nats-server.conf /etc/nats-server.conf
