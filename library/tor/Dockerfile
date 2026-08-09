FROM debian:stable AS build
ARG TOR_VERSION="0.4.8.13"

RUN apt update
RUN apt install -y wget apt-transport-https

RUN apt install -y build-essential libssl-dev ca-certificates libcap-dev libevent-dev libssl-dev liblzma-dev zlib1g-dev libzstd-dev

RUN wget https://www.torproject.org/dist/tor-${TOR_VERSION}.tar.gz
RUN tar xf tor-${TOR_VERSION}.tar.gz

WORKDIR tor-${TOR_VERSION}

COPY ./0001-do-not-enforce-directory-permissions.patch 0001-do-not-enforce-directory-permissions.patch
RUN patch -p1 < 0001-do-not-enforce-directory-permissions.patch

RUN CFLAGS="-UHAVE_SYSCTL -UHAVE_FSYNC -U__linux__" \
    ./configure \
        --enable-gpl \
        --enable-lzma \
        --enable-zstd \
        --disable-seccomp \
        --disable-html-manual \
        --disable-asciidoc \
        --disable-manpage \
        --disable-unittests


RUN make
RUN make install

RUN strip /usr/local/bin/tor

WORKDIR /


FROM scratch

COPY --from=build /usr/local/bin/tor /usr/local/bin/tor
COPY ./config/torrc /etc/tor/torrc

COPY ./data /data

COPY --from=build /etc/passwd /etc/passwd
COPY --from=build /etc/nsswitch.conf /etc/nsswitch.conf
COPY --from=build /usr/local/share/tor/geoip /usr/local/share/tor/geoip

COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
COPY --from=build /lib/x86_64-linux-gnu/libz.so.1 /lib/x86_64-linux-gnu/libz.so.1
COPY --from=build /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/libm.so.6
COPY --from=build /lib/x86_64-linux-gnu/libevent-2.1.so.7 /lib/x86_64-linux-gnu/libevent-2.1.so.7
COPY --from=build /lib/x86_64-linux-gnu/libssl.so.3 /lib/x86_64-linux-gnu/libssl.so.3
COPY --from=build /lib/x86_64-linux-gnu/libcrypto.so.3 /lib/x86_64-linux-gnu/libcrypto.so.3

COPY --from=build /lib/x86_64-linux-gnu/libgcc_s.so.1 /lib/x86_64-linux-gnu/libgcc_s.so.1
COPY --from=build /lib/x86_64-linux-gnu/libcap.so.2 /lib/x86_64-linux-gnu/libcap.so.2
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6

COPY --from=build /etc/ld.so.cache /etc/ld.so.cache
