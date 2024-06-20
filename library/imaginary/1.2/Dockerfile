FROM golang:1.21.6-bookworm AS build

ARG IMAGINARY_VERSION=1.2.4

RUN set -xe; \
    apt-get -yqq update; \
    apt-get -yqq install \
        wget \
        unzip \
        libvips-dev \
    ;

WORKDIR /src

RUN set -xe; \
    wget https://github.com/h2non/imaginary/archive/refs/tags/v${IMAGINARY_VERSION}.zip; \
    unzip v${IMAGINARY_VERSION}.zip \
    ;

RUN set -xe; \
    cd imaginary-${IMAGINARY_VERSION}; \
    CGO_ENABLED=1 go build -buildmode=pie -o /usr/bin/imaginary \
    ;

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

# Imaginary binary
COPY --from=build /usr/bin/imaginary /usr/bin/imaginary

# Libraries
COPY --from=build /lib/x86_64-linux-gnu/libvips.so.42 /lib/x86_64-linux-gnu/libvips.so.42
COPY --from=build /lib/x86_64-linux-gnu/libgobject-2.0.so.0 /lib/x86_64-linux-gnu/libgobject-2.0.so.0
COPY --from=build /lib/x86_64-linux-gnu/libglib-2.0.so.0 /lib/x86_64-linux-gnu/libglib-2.0.so.0
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=build /lib/x86_64-linux-gnu/libgio-2.0.so.0 /lib/x86_64-linux-gnu/libgio-2.0.so.0
COPY --from=build /lib/x86_64-linux-gnu/libgmodule-2.0.so.0 /lib/x86_64-linux-gnu/libgmodule-2.0.so.0
COPY --from=build /lib/x86_64-linux-gnu/libexpat.so.1 /lib/x86_64-linux-gnu/libexpat.so.1
COPY --from=build /lib/x86_64-linux-gnu/libz.so.1 /lib/x86_64-linux-gnu/libz.so.1
COPY --from=build /lib/x86_64-linux-gnu/libgsf-1.so.114 /lib/x86_64-linux-gnu/libgsf-1.so.114
COPY --from=build /lib/x86_64-linux-gnu/libfftw3.so.3 /lib/x86_64-linux-gnu/libfftw3.so.3
COPY --from=build /lib/x86_64-linux-gnu/libcfitsio.so.10 /lib/x86_64-linux-gnu/libcfitsio.so.10
COPY --from=build /lib/x86_64-linux-gnu/libimagequant.so.0 /lib/x86_64-linux-gnu/libimagequant.so.0
COPY --from=build /lib/x86_64-linux-gnu/libcgif.so.0 /lib/x86_64-linux-gnu/libcgif.so.0
COPY --from=build /lib/x86_64-linux-gnu/libexif.so.12 /lib/x86_64-linux-gnu/libexif.so.12
COPY --from=build /lib/x86_64-linux-gnu/libjpeg.so.62 /lib/x86_64-linux-gnu/libjpeg.so.62
COPY --from=build /lib/x86_64-linux-gnu/libpng16.so.16 /lib/x86_64-linux-gnu/libpng16.so.16
COPY --from=build /lib/x86_64-linux-gnu/libwebp.so.7 /lib/x86_64-linux-gnu/libwebp.so.7
COPY --from=build /lib/x86_64-linux-gnu/libwebpmux.so.3 /lib/x86_64-linux-gnu/libwebpmux.so.3
COPY --from=build /lib/x86_64-linux-gnu/libwebpdemux.so.2 /lib/x86_64-linux-gnu/libwebpdemux.so.2
COPY --from=build /lib/x86_64-linux-gnu/libpangocairo-1.0.so.0 /lib/x86_64-linux-gnu/libpangocairo-1.0.so.0
COPY --from=build /lib/x86_64-linux-gnu/libpango-1.0.so.0 /lib/x86_64-linux-gnu/libpango-1.0.so.0
COPY --from=build /lib/x86_64-linux-gnu/libcairo.so.2 /lib/x86_64-linux-gnu/libcairo.so.2
COPY --from=build /lib/x86_64-linux-gnu/libpangoft2-1.0.so.0 /lib/x86_64-linux-gnu/libpangoft2-1.0.so.0
COPY --from=build /lib/x86_64-linux-gnu/libfontconfig.so.1 /lib/x86_64-linux-gnu/libfontconfig.so.1
COPY --from=build /lib/x86_64-linux-gnu/libtiff.so.6 /lib/x86_64-linux-gnu/libtiff.so.6
COPY --from=build /lib/x86_64-linux-gnu/librsvg-2.so.2 /lib/x86_64-linux-gnu/librsvg-2.so.2
COPY --from=build /lib/x86_64-linux-gnu/libmatio.so.11 /lib/x86_64-linux-gnu/libmatio.so.11
COPY --from=build /lib/x86_64-linux-gnu/liblcms2.so.2 /lib/x86_64-linux-gnu/liblcms2.so.2
COPY --from=build /lib/x86_64-linux-gnu/libOpenEXR-3_1.so.30 /lib/x86_64-linux-gnu/libOpenEXR-3_1.so.30
COPY --from=build /lib/x86_64-linux-gnu/libopenjp2.so.7 /lib/x86_64-linux-gnu/libopenjp2.so.7
COPY --from=build /lib/x86_64-linux-gnu/liborc-0.4.so.0 /lib/x86_64-linux-gnu/liborc-0.4.so.0
COPY --from=build /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/libm.so.6
COPY --from=build /lib/x86_64-linux-gnu/libffi.so.8 /lib/x86_64-linux-gnu/libffi.so.8
COPY --from=build /lib/x86_64-linux-gnu/libpcre2-8.so.0 /lib/x86_64-linux-gnu/libpcre2-8.so.0
COPY --from=build /lib/x86_64-linux-gnu/libmount.so.1 /lib/x86_64-linux-gnu/libmount.so.1
COPY --from=build /lib/x86_64-linux-gnu/libselinux.so.1 /lib/x86_64-linux-gnu/libselinux.so.1
COPY --from=build /lib/x86_64-linux-gnu/libxml2.so.2 /lib/x86_64-linux-gnu/libxml2.so.2
COPY --from=build /lib/x86_64-linux-gnu/libbz2.so.1.0 /lib/x86_64-linux-gnu/libbz2.so.1.0
COPY --from=build /lib/x86_64-linux-gnu/libcurl-gnutls.so.4 /lib/x86_64-linux-gnu/libcurl-gnutls.so.4
COPY --from=build /lib/x86_64-linux-gnu/libgomp.so.1 /lib/x86_64-linux-gnu/libgomp.so.1
COPY --from=build /lib/x86_64-linux-gnu/libharfbuzz.so.0 /lib/x86_64-linux-gnu/libharfbuzz.so.0
COPY --from=build /lib/x86_64-linux-gnu/libfribidi.so.0 /lib/x86_64-linux-gnu/libfribidi.so.0
COPY --from=build /lib/x86_64-linux-gnu/libthai.so.0 /lib/x86_64-linux-gnu/libthai.so.0
COPY --from=build /lib/x86_64-linux-gnu/libpixman-1.so.0 /lib/x86_64-linux-gnu/libpixman-1.so.0
COPY --from=build /lib/x86_64-linux-gnu/libfreetype.so.6 /lib/x86_64-linux-gnu/libfreetype.so.6
COPY --from=build /lib/x86_64-linux-gnu/libxcb-shm.so.0 /lib/x86_64-linux-gnu/libxcb-shm.so.0
COPY --from=build /lib/x86_64-linux-gnu/libxcb.so.1 /lib/x86_64-linux-gnu/libxcb.so.1
COPY --from=build /lib/x86_64-linux-gnu/libxcb-render.so.0 /lib/x86_64-linux-gnu/libxcb-render.so.0
COPY --from=build /lib/x86_64-linux-gnu/libXrender.so.1 /lib/x86_64-linux-gnu/libXrender.so.1
COPY --from=build /lib/x86_64-linux-gnu/libX11.so.6 /lib/x86_64-linux-gnu/libX11.so.6
COPY --from=build /lib/x86_64-linux-gnu/libXext.so.6 /lib/x86_64-linux-gnu/libXext.so.6
COPY --from=build /lib/x86_64-linux-gnu/libzstd.so.1 /lib/x86_64-linux-gnu/libzstd.so.1
COPY --from=build /lib/x86_64-linux-gnu/liblzma.so.5 /lib/x86_64-linux-gnu/liblzma.so.5
COPY --from=build /lib/x86_64-linux-gnu/libLerc.so.4 /lib/x86_64-linux-gnu/libLerc.so.4
COPY --from=build /lib/x86_64-linux-gnu/libjbig.so.0 /lib/x86_64-linux-gnu/libjbig.so.0
COPY --from=build /lib/x86_64-linux-gnu/libdeflate.so.0 /lib/x86_64-linux-gnu/libdeflate.so.0
COPY --from=build /lib/x86_64-linux-gnu/libcairo-gobject.so.2 /lib/x86_64-linux-gnu/libcairo-gobject.so.2
COPY --from=build /lib/x86_64-linux-gnu/libgdk_pixbuf-2.0.so.0 /lib/x86_64-linux-gnu/libgdk_pixbuf-2.0.so.0
COPY --from=build /lib/x86_64-linux-gnu/libgcc_s.so.1 /lib/x86_64-linux-gnu/libgcc_s.so.1
COPY --from=build /lib/x86_64-linux-gnu/libhdf5_serial.so.103 /lib/x86_64-linux-gnu/libhdf5_serial.so.103
COPY --from=build /lib/x86_64-linux-gnu/libImath-3_1.so.29 /lib/x86_64-linux-gnu/libImath-3_1.so.29
COPY --from=build /lib/x86_64-linux-gnu/libIlmThread-3_1.so.30 /lib/x86_64-linux-gnu/libIlmThread-3_1.so.30
COPY --from=build /lib/x86_64-linux-gnu/libIex-3_1.so.30 /lib/x86_64-linux-gnu/libIex-3_1.so.30
COPY --from=build /lib/x86_64-linux-gnu/libstdc++.so.6 /lib/x86_64-linux-gnu/libstdc++.so.6
COPY --from=build /lib/x86_64-linux-gnu/libblkid.so.1 /lib/x86_64-linux-gnu/libblkid.so.1
COPY --from=build /lib/x86_64-linux-gnu/libicuuc.so.72 /lib/x86_64-linux-gnu/libicuuc.so.72
COPY --from=build /lib/x86_64-linux-gnu/libnghttp2.so.14 /lib/x86_64-linux-gnu/libnghttp2.so.14
COPY --from=build /lib/x86_64-linux-gnu/libidn2.so.0 /lib/x86_64-linux-gnu/libidn2.so.0
COPY --from=build /lib/x86_64-linux-gnu/librtmp.so.1 /lib/x86_64-linux-gnu/librtmp.so.1
COPY --from=build /lib/x86_64-linux-gnu/libssh2.so.1 /lib/x86_64-linux-gnu/libssh2.so.1
COPY --from=build /lib/x86_64-linux-gnu/libpsl.so.5 /lib/x86_64-linux-gnu/libpsl.so.5
COPY --from=build /lib/x86_64-linux-gnu/libnettle.so.8 /lib/x86_64-linux-gnu/libnettle.so.8
COPY --from=build /lib/x86_64-linux-gnu/libgnutls.so.30 /lib/x86_64-linux-gnu/libgnutls.so.30
COPY --from=build /lib/x86_64-linux-gnu/libgssapi_krb5.so.2 /lib/x86_64-linux-gnu/libgssapi_krb5.so.2
COPY --from=build /lib/x86_64-linux-gnu/libldap-2.5.so.0 /lib/x86_64-linux-gnu/libldap-2.5.so.0
COPY --from=build /lib/x86_64-linux-gnu/liblber-2.5.so.0 /lib/x86_64-linux-gnu/liblber-2.5.so.0
COPY --from=build /lib/x86_64-linux-gnu/libbrotlidec.so.1 /lib/x86_64-linux-gnu/libbrotlidec.so.1
COPY --from=build /lib/x86_64-linux-gnu/libgraphite2.so.3 /lib/x86_64-linux-gnu/libgraphite2.so.3
COPY --from=build /lib/x86_64-linux-gnu/libdatrie.so.1 /lib/x86_64-linux-gnu/libdatrie.so.1
COPY --from=build /lib/x86_64-linux-gnu/libXau.so.6 /lib/x86_64-linux-gnu/libXau.so.6
COPY --from=build /lib/x86_64-linux-gnu/libXdmcp.so.6 /lib/x86_64-linux-gnu/libXdmcp.so.6
COPY --from=build /lib/x86_64-linux-gnu/libcrypto.so.3 /lib/x86_64-linux-gnu/libcrypto.so.3
COPY --from=build /lib/x86_64-linux-gnu/libcurl.so.4 /lib/x86_64-linux-gnu/libcurl.so.4
COPY --from=build /lib/x86_64-linux-gnu/libsz.so.2 /lib/x86_64-linux-gnu/libsz.so.2
COPY --from=build /lib/x86_64-linux-gnu/libicudata.so.72 /lib/x86_64-linux-gnu/libicudata.so.72
COPY --from=build /lib/x86_64-linux-gnu/libunistring.so.2 /lib/x86_64-linux-gnu/libunistring.so.2
COPY --from=build /lib/x86_64-linux-gnu/libhogweed.so.6 /lib/x86_64-linux-gnu/libhogweed.so.6
COPY --from=build /lib/x86_64-linux-gnu/libgmp.so.10 /lib/x86_64-linux-gnu/libgmp.so.10
COPY --from=build /lib/x86_64-linux-gnu/libp11-kit.so.0 /lib/x86_64-linux-gnu/libp11-kit.so.0
COPY --from=build /lib/x86_64-linux-gnu/libtasn1.so.6 /lib/x86_64-linux-gnu/libtasn1.so.6
COPY --from=build /lib/x86_64-linux-gnu/libkrb5.so.3 /lib/x86_64-linux-gnu/libkrb5.so.3
COPY --from=build /lib/x86_64-linux-gnu/libk5crypto.so.3 /lib/x86_64-linux-gnu/libk5crypto.so.3
COPY --from=build /lib/x86_64-linux-gnu/libcom_err.so.2 /lib/x86_64-linux-gnu/libcom_err.so.2
COPY --from=build /lib/x86_64-linux-gnu/libkrb5support.so.0 /lib/x86_64-linux-gnu/libkrb5support.so.0
COPY --from=build /lib/x86_64-linux-gnu/libsasl2.so.2 /lib/x86_64-linux-gnu/libsasl2.so.2
COPY --from=build /lib/x86_64-linux-gnu/libbrotlicommon.so.1 /lib/x86_64-linux-gnu/libbrotlicommon.so.1
COPY --from=build /lib/x86_64-linux-gnu/libbsd.so.0 /lib/x86_64-linux-gnu/libbsd.so.0
COPY --from=build /lib/x86_64-linux-gnu/libssl.so.3 /lib/x86_64-linux-gnu/libssl.so.3
COPY --from=build /lib/x86_64-linux-gnu/libaec.so.0 /lib/x86_64-linux-gnu/libaec.so.0
COPY --from=build /lib/x86_64-linux-gnu/libkeyutils.so.1 /lib/x86_64-linux-gnu/libkeyutils.so.1
COPY --from=build /lib/x86_64-linux-gnu/libresolv.so.2 /lib/x86_64-linux-gnu/libresolv.so.2
COPY --from=build /lib/x86_64-linux-gnu/libmd.so.0 /lib/x86_64-linux-gnu/libmd.so.0

COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2

#COPY --from=build /usr/lib /usr/lib
#COPY --from=build /lib/x86_64-linux-gnu /lib/x86_64-linux-gnu
#
## Temporary copy
#COPY --from=build /lib/x86_64-linux-gnu/libtinfo.so.6 /lib/x86_64-linux-gnu/libtinfo.so.6
#COPY --from=build /lib/x86_64-linux-gnu/libdl.so.2 /lib/x86_64-linux-gnu/libdl.so.2
#COPY --from=build /bin/bash /bin/bash
#COPY --from=build /usr/bin/ldd /usr/bin/ldd
