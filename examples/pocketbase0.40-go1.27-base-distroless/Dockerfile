FROM golang:1.27.0-trixie AS build

WORKDIR /app

COPY go.mod ./
COPY main.go .

RUN go get github.com/pocketbase/pocketbase@v0.40.0
RUN go mod tidy

# Patch PocketBase's optimised WAL mode to DELETE mode
# Unikraft currently does not support MAP_SHARED
RUN go mod vendor
RUN find vendor/github.com/pocketbase/pocketbase -type f -name "*.go" -exec sed -i 's/journal_mode=WAL/journal_mode=DELETE/g' {} +
RUN find vendor/github.com/pocketbase/pocketbase -type f -name "*.go" -exec sed -i 's/journal_mode(WAL)/journal_mode(DELETE)/g' {} +

RUN set -xe; \
    go build -v \
      -buildmode=pie \
      -ldflags="-linkmode external -extldflags -static-pie" \
      -tags netgo \
      -o server main.go

FROM gcr.io/distroless/static-debian13@sha256:f2ea2709ac8db56323cbd7d014277f32cb572d9ea124b0076f7aafe5980678fe

COPY --from=build /app/server /server

