FROM golang:1.21-alpine AS build

ARG NTFY_VERSION=v2.11.0

WORKDIR /ntfy

RUN apk add --no-cache git ca-certificates gcc musl-dev && \
    git clone --depth=1 --branch ${NTFY_VERSION} https://github.com/binwiederhier/ntfy.git /ntfy

RUN mkdir -p server/docs server/site && \
    echo "Unikraft Ntfy Docs" > server/docs/index.html && \
    echo "Unikraft Ntfy Web" > server/site/index.html

RUN CGO_ENABLED=1 go build \
    -buildmode=pie \
    -tags sqlite_omit_load_extension,osusergo,netgo \
    -trimpath \
    -ldflags="-linkmode=external -extldflags=-static-pie -s -w" \
    -o /usr/bin/ntfy \
    ./main.go

RUN echo "127.0.0.1 localhost" > /tmp/hosts

FROM scratch

COPY --from=build /usr/bin/ntfy /usr/bin/ntfy
COPY --from=build /tmp/hosts /etc/hosts
COPY --from=build /etc/ssl/certs/ca-certificates.crt /etc/ssl/certs/
COPY ./server.yml /etc/ntfy/server.yml
