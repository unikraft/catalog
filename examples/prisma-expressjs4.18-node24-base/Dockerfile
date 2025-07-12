FROM node:24-alpine3.20 AS base

WORKDIR /app

COPY ./package.json /app/

RUN npm install

FROM alpine:3 AS sys

RUN apk add --no-cache openssl
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

FROM base AS deps

WORKDIR /app
COPY ./package.json /app/
RUN npm install

FROM deps AS build

WORKDIR /app

COPY ./webpack.config.js /app/
COPY ./src /app/src
COPY ./prisma /app/prisma

RUN set -xe; \
    npx prisma generate; \
    npx prisma migrate deploy; \
    npx prisma db seed; \
    npm run build \
    ;

FROM scratch

COPY --from=sys /target/etc /etc
COPY --from=sys /usr/share/zoneinfo/Etc/UTC /usr/share/zoneinfo/Etc/UTC
COPY --from=sys /etc/ssl/certs/ca-certificates.crt /etc/ssl/certs/ca-certificates.crt
COPY --from=sys /blank /tmp

# Node binary
COPY --from=build /usr/local/bin/node /usr/bin/node

# System libraries
COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=build /usr/lib/libgcc_s.so.1 /usr/lib/libgcc_s.so.1
COPY --from=build /usr/lib/libstdc++.so.6 /usr/lib/libstdc++.so.6

COPY --from=build /app/dist /usr/src

# Distribution configuration
COPY --from=build /etc/os-release /etc/os-release

# Library files
COPY --from=build /lib/libcrypto.so.3 /lib/libcrypto.so.3
COPY --from=build /lib/libssl.so.3 /lib/libssl.so.3

# rest-express + Prisma
COPY --from=build /app/dist /usr/src
