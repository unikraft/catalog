# chrony built from source with HAVE_RECVMMSG removed
FROM alpine:3.24 AS build

ARG CHRONY_VERSION=4.8

RUN apk add --no-cache gcc make musl-dev nettle-dev
ADD https://chrony-project.org/releases/chrony-${CHRONY_VERSION}.tar.gz /chrony.tar.gz
RUN tar xzf /chrony.tar.gz && \
    cd /chrony-${CHRONY_VERSION} && \
    ./configure --prefix=/usr --sysconfdir=/etc/chrony \
                --disable-cmdmon --disable-refclock --disable-ipv6 \
                --without-libcap --without-seccomp \
                --without-nss --without-tomcrypt \
                --without-gnutls && \
    sed -i '/HAVE_RECVMMSG/d' config.h && \
    ! grep -q HAVE_RECVMMSG config.h && \
    make -j"$(nproc)" chronyd && \
    strip chronyd && \
    cp chronyd /usr/sbin/chronyd

# runtime dirs, staged so scratch COPY can pick them up
RUN mkdir -p /out/etc/chrony /out/run/chrony /out/var/lib/chrony

FROM scratch

COPY --from=build /usr/sbin/chronyd /usr/sbin/chronyd
COPY --from=build /etc/passwd /etc/passwd
COPY --from=build /etc/group /etc/group
COPY --from=build /out/etc/chrony /etc/chrony
COPY --from=build /out/run/chrony /run/chrony
COPY --from=build /out/var/lib/chrony /var/lib/chrony

# musl loader (+ libc alias) and nettle, for SECHASH symmetric-key auth
COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/libc.musl-x86_64.so.1
COPY --from=build /usr/lib/libnettle.so.8 /usr/lib/libnettle.so.8

# Static configuration
COPY ./conf/chrony.conf /etc/chrony/chrony.conf
COPY ./conf/resolv.conf /etc/resolv.conf
