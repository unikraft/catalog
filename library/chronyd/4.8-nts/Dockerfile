# chrony built from source with HAVE_RECVMMSG removed
FROM alpine:3.24 AS build

ARG CHRONY_VERSION=4.8

RUN apk add --no-cache gcc make musl-dev gnutls-dev nettle-dev ca-certificates
ADD https://chrony-project.org/releases/chrony-${CHRONY_VERSION}.tar.gz /chrony.tar.gz
RUN tar xzf /chrony.tar.gz && \
    cd /chrony-${CHRONY_VERSION} && \
    ./configure --prefix=/usr --sysconfdir=/etc/chrony \
                --disable-refclock --disable-ipv6 \
                --without-libcap --without-seccomp \
                --without-nss --without-tomcrypt && \
    grep -q '#define FEAT_NTS 1' config.h && \
    grep -q '#define HAVE_NETTLE' config.h && \
    grep -q '#define FEAT_CMDMON 1' config.h && \
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

# musl loader (+ libc alias)
COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/libc.musl-x86_64.so.1

# gnutls and its dependency closure (ldd chronyd)
COPY --from=build /usr/lib/libgnutls.so.30 /usr/lib/libgnutls.so.30
COPY --from=build /usr/lib/libz.so.1 /usr/lib/libz.so.1
COPY --from=build /usr/lib/libzstd.so.1 /usr/lib/libzstd.so.1
COPY --from=build /usr/lib/libbrotlienc.so.1 /usr/lib/libbrotlienc.so.1
COPY --from=build /usr/lib/libbrotlidec.so.1 /usr/lib/libbrotlidec.so.1
COPY --from=build /usr/lib/libbrotlicommon.so.1 /usr/lib/libbrotlicommon.so.1
COPY --from=build /usr/lib/libp11-kit.so.0 /usr/lib/libp11-kit.so.0
COPY --from=build /usr/lib/libidn2.so.0 /usr/lib/libidn2.so.0
COPY --from=build /usr/lib/libunistring.so.5 /usr/lib/libunistring.so.5
COPY --from=build /usr/lib/libtasn1.so.6 /usr/lib/libtasn1.so.6
COPY --from=build /usr/lib/libhogweed.so.6 /usr/lib/libhogweed.so.6
COPY --from=build /usr/lib/libnettle.so.8 /usr/lib/libnettle.so.8
COPY --from=build /usr/lib/libgmp.so.10 /usr/lib/libgmp.so.10
COPY --from=build /usr/lib/libffi.so.8 /usr/lib/libffi.so.8

# CA bundle for NTS-KE certificate validation
COPY --from=build /etc/ssl/certs/ca-certificates.crt /etc/ssl/certs/ca-certificates.crt

# Static configuration
COPY ./conf/chrony.conf /etc/chrony/chrony.conf
COPY ./conf/resolv.conf /etc/resolv.conf
