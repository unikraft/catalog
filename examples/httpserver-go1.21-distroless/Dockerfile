FROM golang:1.21.3-bookworm AS build

WORKDIR /src

COPY ./server.go /src/server.go

RUN set -xe; \
    CGO_ENABLED=1 \
    go build \
      -buildmode=pie \
      -ldflags "-linkmode external -extldflags '-static-pie'" \
      -tags netgo \
      -o /server server.go \
    ;

FROM gcr.io/distroless/static-debian13:latest

COPY --from=build /server /server