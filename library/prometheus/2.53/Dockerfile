FROM alpine:3.22 AS builder

RUN set -xe; \
    echo "https://dl-cdn.alpinelinux.org/alpine/edge/community" \
      >> /etc/apk/repositories; \
    apk update; \
    apk add --no-cache \
      prometheus=2.53.4-r2 \
      tzdata

FROM alpine:3.22 AS sys
RUN set -xe; \
    apk add --no-cache \
      tzdata; \
    mkdir -p /target/etc; \
    ln -sf ../usr/share/zoneinfo/Etc/UTC /target/etc/localtime; \
    echo "Etc/UTC" > /target/etc/timezone; \
    mkdir /blank

FROM scratch

COPY --from=sys /target/etc /etc
COPY --from=sys /usr/share/zoneinfo/Etc/UTC /usr/share/zoneinfo/Etc/UTC
COPY --from=sys /blank /data

COPY --from=builder /usr/bin/prometheus /usr/bin/prometheus
COPY --from=builder /usr/bin/promtool   /usr/bin/promtool
COPY --from=builder /etc/prometheus /etc/prometheus
COPY --from=builder /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1

COPY ./prometheus.yml /prometheus.yml
