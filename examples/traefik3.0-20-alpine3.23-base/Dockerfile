FROM node:20-alpine3.23 AS builder

WORKDIR /traefik-src

RUN apk add --no-cache git gcc musl-dev ca-certificates go

RUN git clone --depth 1 -b v3.0.0 https://github.com/traefik/traefik.git .

RUN cd webui && yarn install && yarn build

RUN CGO_ENABLED=0 go build -buildmode=pie -ldflags '-s -w' -o /traefik-binary ./cmd/traefik

FROM scratch

COPY --from=builder /traefik-binary /usr/local/bin/traefik

COPY --from=builder /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1

COPY dynamic.yml /etc/traefik/dynamic.yml

COPY --from=builder /etc/ssl/certs/ca-certificates.crt /etc/ssl/certs/ca-certificates.crt

ENTRYPOINT ["/usr/local/bin/traefik"]
