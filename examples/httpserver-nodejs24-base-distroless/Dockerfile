FROM node:24-alpine3.20 AS node

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

FROM cgr.dev/chainguard/node:latest

# Node HTTP server
COPY ./src /usr/src
