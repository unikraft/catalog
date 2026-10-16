FROM golang:1.27.0-bookworm AS build

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

FROM gcr.io/distroless/cc-debian12@sha256:e5d81ddde149641e2a9ba55be4545bc125c67de07508b03ba4c22e6eb0ded5aa

COPY --from=build /server /bin/server

