FROM golang:1.21.3-bookworm AS build

WORKDIR /src

COPY ./src/go.mod ./src/go.sum ./

RUN go mod download

COPY ./src/ ./

RUN CGO_ENABLED=1 go build \
    -buildmode=pie \
    -ldflags "-linkmode external -extldflags -static-pie" \
    -tags netgo \
    -o /server \
    .

FROM scratch

COPY --from=build /server /server