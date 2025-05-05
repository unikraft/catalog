FROM nats:2.10-alpine AS nats

RUN  apk add build-base; \
    wget -q "https://go.dev/dl/go1.24.0.linux-amd64.tar.gz"; \
    tar -C /usr/local -xzf go1.24.0.linux-amd64.tar.gz; \
    export PATH=$PATH:/usr/local/go/bin; \
    wget -q "https://github.com/nats-io/nats-server/archive/refs/tags/v2.10.26.tar.gz"; \
    mkdir nats; \
    tar -xzf v2.10.26.tar.gz; \
    cd nats-server-2.10.26; \
    go build -ldflags "-linkmode 'external' -extldflags '-pie'" -buildmode=pie -o /usr/local/nats-server; 

FROM scratch

COPY --from=nats /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=nats /usr/local/nats-server /usr/bin/nats-server
COPY --from=nats /etc/nats/nats-server.conf /etc/nats-server.conf
