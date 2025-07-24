FROM --platform=linux/x86-64 debian:bookworm AS build

RUN set -xe; \
    apt update; \
		apt install -y \
		git ca-certificates build-essential libsdl2-dev libvorbis-dev libxmp-dev \
		;

WORKDIR /root

RUN set -xe; \
		mkdir -p /root/.local/share/OpenArena/baseoa; \
		git clone --depth=1 --branch no-forks \
		https://github.com/BVRazvan/engine.git; \
		cd engine && make && cp build/release-linux-x86_64/oa_ded.x86_64 \
		/root/ && cp -r baseoa/ /root/.local/share/OpenArena \
		;

RUN chmod +x oa_ded.x86_64

EXPOSE 27960/udp

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

COPY --from=build /root/oa_ded.x86_64 /oa_ded.x86_64
COPY --from=build /root/.local/share/OpenArena //.local/share/OpenArena
COPY --from=build /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/libm.so.6
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2

