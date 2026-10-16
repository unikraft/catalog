FROM golang:1.27.0-trixie AS build

WORKDIR /app

COPY go.mod ./
COPY main.go .

RUN set -xe; \
    # Force patch for crypto library
    go get golang.org/x/crypto@v0.55.0; \
    go mod tidy; \
    go build -v \
        -buildmode=pie \
        -ldflags "-linkmode external -extldflags -static-pie" \
        -tags netgo \
        -o server main.go

FROM gcr.io/distroless/static-debian13@sha256:f2ea2709ac8db56323cbd7d014277f32cb572d9ea124b0076f7aafe5980678fe

COPY --from=build /app/server /server

