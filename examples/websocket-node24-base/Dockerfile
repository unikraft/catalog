FROM node:24-alpine AS node

WORKDIR /usr/src
COPY package.json .
COPY package-lock.json .
RUN npm install

FROM alpine:3 AS sys

RUN set -xe; \
    mkdir -p /target/etc; \
    mkdir -p /blank; \
    apk --no-cache add \
    ca-certificates \
    tzdata \
    ; \
    update-ca-certificates; \
    ln -sf ../usr/share/zoneinfo/Etc/UTC /target/etc/localtime; \
    echo "Etc/UTC" > /target/etc/timezone;

FROM scratch

COPY --from=sys /target/etc /etc
COPY --from=sys /usr/share/zoneinfo/Etc/UTC /usr/share/zoneinfo/Etc/UTC
COPY --from=sys /etc/ssl/certs/ca-certificates.crt /etc/ssl/certs/ca-certificates.crt
COPY --from=sys /blank /tmp

# Node binary
COPY --from=node /usr/local/bin/node /usr/bin/node

# System libraries
COPY --from=node /etc/ssl/openssl.cnf /etc/ssl/openssl.cnf
COPY --from=node /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=node /usr/lib/libgcc_s.so.1 /usr/lib/libgcc_s.so.1
COPY --from=node /usr/lib/libstdc++.so.6 /usr/lib/libstdc++.so.6

# Node HTTP server
COPY --from=node /usr/src /usr/src
COPY ./src /usr/src
