FROM debian:bookworm AS build

RUN set -xe; \
    apt-get -yqq update; \
    apt-get -yqq install \
        libcups2 \
        libnss3 \
        libatk1.0-0 \
        libnspr4 \
        libpango1.0-0 \
        libasound2 \
        libatspi2.0-0 \
        libxdamage1 \
        libatk-bridge2.0-0 \
        libxkbcommon0; \
    apt-get -yqq install \
        git \
        nodejs \
        npm \
    ;

RUN mkdir /src
WORKDIR /src

RUN npm install puppeteer

RUN mkdir /home/tmp
RUN mkdir -p /home/proc/self

FROM scratch

# Create required directories.
COPY --from=build /home/tmp /tmp
COPY --from=build /home/proc/self /proc/self

# Chrome binary
COPY --from=build /root/.cache/puppeteer/chrome /root/.cache/puppeteer/chrome
COPY --from=build /root/.cache/puppeteer/chrome/linux-*/chrome-linux64/chrome /proc/self/exe

# Chrome libraries
COPY --from=build /lib/x86_64-linux-gnu/libdl.so.2 /lib/x86_64-linux-gnu/libdl.so.2
COPY --from=build /lib/x86_64-linux-gnu/libpthread.so.0 /lib/x86_64-linux-gnu/libpthread.so.0
COPY --from=build /lib/x86_64-linux-gnu/libgobject-2.0.so.0 /lib/x86_64-linux-gnu/libgobject-2.0.so.0
COPY --from=build /lib/x86_64-linux-gnu/libglib-2.0.so.0 /lib/x86_64-linux-gnu/libglib-2.0.so.0
COPY --from=build /lib/x86_64-linux-gnu/libnss3.so /lib/x86_64-linux-gnu/libnss3.so
COPY --from=build /lib/x86_64-linux-gnu/libnssutil3.so /lib/x86_64-linux-gnu/libnssutil3.so
COPY --from=build /lib/x86_64-linux-gnu/libsmime3.so /lib/x86_64-linux-gnu/libsmime3.so
COPY --from=build /lib/x86_64-linux-gnu/libnspr4.so /lib/x86_64-linux-gnu/libnspr4.so
COPY --from=build /lib/x86_64-linux-gnu/libatk-1.0.so.0 /lib/x86_64-linux-gnu/libatk-1.0.so.0
COPY --from=build /lib/x86_64-linux-gnu/libatk-bridge-2.0.so.0 /lib/x86_64-linux-gnu/libatk-bridge-2.0.so.0
COPY --from=build /lib/x86_64-linux-gnu/libcups.so.2 /lib/x86_64-linux-gnu/libcups.so.2
COPY --from=build /lib/x86_64-linux-gnu/libgio-2.0.so.0 /lib/x86_64-linux-gnu/libgio-2.0.so.0
COPY --from=build /lib/x86_64-linux-gnu/libdrm.so.2 /lib/x86_64-linux-gnu/libdrm.so.2
COPY --from=build /lib/x86_64-linux-gnu/libdbus-1.so.3 /lib/x86_64-linux-gnu/libdbus-1.so.3
COPY --from=build /lib/x86_64-linux-gnu/libexpat.so.1 /lib/x86_64-linux-gnu/libexpat.so.1
COPY --from=build /lib/x86_64-linux-gnu/libxcb.so.1 /lib/x86_64-linux-gnu/libxcb.so.1
COPY --from=build /lib/x86_64-linux-gnu/libxkbcommon.so.0 /lib/x86_64-linux-gnu/libxkbcommon.so.0
COPY --from=build /lib/x86_64-linux-gnu/libatspi.so.0 /lib/x86_64-linux-gnu/libatspi.so.0
COPY --from=build /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/libm.so.6
COPY --from=build /lib/x86_64-linux-gnu/libX11.so.6 /lib/x86_64-linux-gnu/libX11.so.6
COPY --from=build /lib/x86_64-linux-gnu/libXcomposite.so.1 /lib/x86_64-linux-gnu/libXcomposite.so.1
COPY --from=build /lib/x86_64-linux-gnu/libXdamage.so.1 /lib/x86_64-linux-gnu/libXdamage.so.1
COPY --from=build /lib/x86_64-linux-gnu/libXext.so.6 /lib/x86_64-linux-gnu/libXext.so.6
COPY --from=build /lib/x86_64-linux-gnu/libXfixes.so.3 /lib/x86_64-linux-gnu/libXfixes.so.3
COPY --from=build /lib/x86_64-linux-gnu/libXrandr.so.2 /lib/x86_64-linux-gnu/libXrandr.so.2
COPY --from=build /lib/x86_64-linux-gnu/libgbm.so.1 /lib/x86_64-linux-gnu/libgbm.so.1
COPY --from=build /lib/x86_64-linux-gnu/libpango-1.0.so.0 /lib/x86_64-linux-gnu/libpango-1.0.so.0
COPY --from=build /lib/x86_64-linux-gnu/libcairo.so.2 /lib/x86_64-linux-gnu/libcairo.so.2
COPY --from=build /lib/x86_64-linux-gnu/libasound.so.2 /lib/x86_64-linux-gnu/libasound.so.2
COPY --from=build /lib/x86_64-linux-gnu/libgcc_s.so.1 /lib/x86_64-linux-gnu/libgcc_s.so.1
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
COPY --from=build /lib/x86_64-linux-gnu/libffi.so.8 /lib/x86_64-linux-gnu/libffi.so.8
COPY --from=build /lib/x86_64-linux-gnu/libpcre2-8.so.0 /lib/x86_64-linux-gnu/libpcre2-8.so.0
COPY --from=build /lib/x86_64-linux-gnu/libplc4.so /lib/x86_64-linux-gnu/libplc4.so
COPY --from=build /lib/x86_64-linux-gnu/libplds4.so /lib/x86_64-linux-gnu/libplds4.so
COPY --from=build /lib/x86_64-linux-gnu/libgssapi_krb5.so.2 /lib/x86_64-linux-gnu/libgssapi_krb5.so.2
COPY --from=build /lib/x86_64-linux-gnu/libavahi-common.so.3 /lib/x86_64-linux-gnu/libavahi-common.so.3
COPY --from=build /lib/x86_64-linux-gnu/libavahi-client.so.3 /lib/x86_64-linux-gnu/libavahi-client.so.3
COPY --from=build /lib/x86_64-linux-gnu/libgnutls.so.30 /lib/x86_64-linux-gnu/libgnutls.so.30
COPY --from=build /lib/x86_64-linux-gnu/libz.so.1 /lib/x86_64-linux-gnu/libz.so.1
COPY --from=build /lib/x86_64-linux-gnu/libgmodule-2.0.so.0 /lib/x86_64-linux-gnu/libgmodule-2.0.so.0
COPY --from=build /lib/x86_64-linux-gnu/libmount.so.1 /lib/x86_64-linux-gnu/libmount.so.1
COPY --from=build /lib/x86_64-linux-gnu/libselinux.so.1 /lib/x86_64-linux-gnu/libselinux.so.1
COPY --from=build /lib/x86_64-linux-gnu/libsystemd.so.0 /lib/x86_64-linux-gnu/libsystemd.so.0
COPY --from=build /lib/x86_64-linux-gnu/libXau.so.6 /lib/x86_64-linux-gnu/libXau.so.6
COPY --from=build /lib/x86_64-linux-gnu/libXdmcp.so.6 /lib/x86_64-linux-gnu/libXdmcp.so.6
COPY --from=build /lib/x86_64-linux-gnu/libXi.so.6 /lib/x86_64-linux-gnu/libXi.so.6
COPY --from=build /lib/x86_64-linux-gnu/libXrender.so.1 /lib/x86_64-linux-gnu/libXrender.so.1
COPY --from=build /lib/x86_64-linux-gnu/libwayland-server.so.0 /lib/x86_64-linux-gnu/libwayland-server.so.0
COPY --from=build /lib/x86_64-linux-gnu/libfribidi.so.0 /lib/x86_64-linux-gnu/libfribidi.so.0
COPY --from=build /lib/x86_64-linux-gnu/libthai.so.0 /lib/x86_64-linux-gnu/libthai.so.0
COPY --from=build /lib/x86_64-linux-gnu/libharfbuzz.so.0 /lib/x86_64-linux-gnu/libharfbuzz.so.0
COPY --from=build /lib/x86_64-linux-gnu/libpixman-1.so.0 /lib/x86_64-linux-gnu/libpixman-1.so.0
COPY --from=build /lib/x86_64-linux-gnu/libfontconfig.so.1 /lib/x86_64-linux-gnu/libfontconfig.so.1
COPY --from=build /lib/x86_64-linux-gnu/libfreetype.so.6 /lib/x86_64-linux-gnu/libfreetype.so.6
COPY --from=build /lib/x86_64-linux-gnu/libpng16.so.16 /lib/x86_64-linux-gnu/libpng16.so.16
COPY --from=build /lib/x86_64-linux-gnu/libxcb-shm.so.0 /lib/x86_64-linux-gnu/libxcb-shm.so.0
COPY --from=build /lib/x86_64-linux-gnu/libxcb-render.so.0 /lib/x86_64-linux-gnu/libxcb-render.so.0
COPY --from=build /lib/x86_64-linux-gnu/libkrb5.so.3 /lib/x86_64-linux-gnu/libkrb5.so.3
COPY --from=build /lib/x86_64-linux-gnu/libk5crypto.so.3 /lib/x86_64-linux-gnu/libk5crypto.so.3
COPY --from=build /lib/x86_64-linux-gnu/libcom_err.so.2 /lib/x86_64-linux-gnu/libcom_err.so.2
COPY --from=build /lib/x86_64-linux-gnu/libkrb5support.so.0 /lib/x86_64-linux-gnu/libkrb5support.so.0
COPY --from=build /lib/x86_64-linux-gnu/libp11-kit.so.0 /lib/x86_64-linux-gnu/libp11-kit.so.0
COPY --from=build /lib/x86_64-linux-gnu/libidn2.so.0 /lib/x86_64-linux-gnu/libidn2.so.0
COPY --from=build /lib/x86_64-linux-gnu/libunistring.so.2 /lib/x86_64-linux-gnu/libunistring.so.2
COPY --from=build /lib/x86_64-linux-gnu/libtasn1.so.6 /lib/x86_64-linux-gnu/libtasn1.so.6
COPY --from=build /lib/x86_64-linux-gnu/libnettle.so.8 /lib/x86_64-linux-gnu/libnettle.so.8
COPY --from=build /lib/x86_64-linux-gnu/libhogweed.so.6 /lib/x86_64-linux-gnu/libhogweed.so.6
COPY --from=build /lib/x86_64-linux-gnu/libgmp.so.10 /lib/x86_64-linux-gnu/libgmp.so.10
COPY --from=build /lib/x86_64-linux-gnu/libblkid.so.1 /lib/x86_64-linux-gnu/libblkid.so.1
COPY --from=build /lib/x86_64-linux-gnu/libcap.so.2 /lib/x86_64-linux-gnu/libcap.so.2
COPY --from=build /lib/x86_64-linux-gnu/libgcrypt.so.20 /lib/x86_64-linux-gnu/libgcrypt.so.20
COPY --from=build /lib/x86_64-linux-gnu/liblzma.so.5 /lib/x86_64-linux-gnu/liblzma.so.5
COPY --from=build /lib/x86_64-linux-gnu/libzstd.so.1 /lib/x86_64-linux-gnu/libzstd.so.1
COPY --from=build /lib/x86_64-linux-gnu/liblz4.so.1 /lib/x86_64-linux-gnu/liblz4.so.1
COPY --from=build /lib/x86_64-linux-gnu/libbsd.so.0 /lib/x86_64-linux-gnu/libbsd.so.0
COPY --from=build /lib/x86_64-linux-gnu/libdatrie.so.1 /lib/x86_64-linux-gnu/libdatrie.so.1
COPY --from=build /lib/x86_64-linux-gnu/libgraphite2.so.3 /lib/x86_64-linux-gnu/libgraphite2.so.3
COPY --from=build /lib/x86_64-linux-gnu/libbrotlidec.so.1 /lib/x86_64-linux-gnu/libbrotlidec.so.1
COPY --from=build /lib/x86_64-linux-gnu/libkeyutils.so.1 /lib/x86_64-linux-gnu/libkeyutils.so.1
COPY --from=build /lib/x86_64-linux-gnu/libresolv.so.2 /lib/x86_64-linux-gnu/libresolv.so.2
COPY --from=build /lib/x86_64-linux-gnu/libgpg-error.so.0 /lib/x86_64-linux-gnu/libgpg-error.so.0
COPY --from=build /lib/x86_64-linux-gnu/libmd.so.0 /lib/x86_64-linux-gnu/libmd.so.0
COPY --from=build /lib/x86_64-linux-gnu/libbrotlicommon.so.1 /lib/x86_64-linux-gnu/libbrotlicommon.so.1


# Node binary
COPY --from=build /usr/bin/node /usr/local/bin/node

# Node files
COPY --from=build /usr/share/nodejs /usr/share/nodejs

# System libraries
COPY --from=build /lib/x86_64-linux-gnu/libnode.so.108 /lib/x86_64-linux-gnu/libnode.so.108
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=build /lib/x86_64-linux-gnu/libz.so.1 /lib/x86_64-linux-gnu/libz.so.1
COPY --from=build /lib/x86_64-linux-gnu/libuv.so.1 /lib/x86_64-linux-gnu/libuv.so.1
COPY --from=build /lib/x86_64-linux-gnu/libbrotlidec.so.1 /lib/x86_64-linux-gnu/libbrotlidec.so.1
COPY --from=build /lib/x86_64-linux-gnu/libbrotlienc.so.1 /lib/x86_64-linux-gnu/libbrotlienc.so.1
COPY --from=build /lib/x86_64-linux-gnu/libcares.so.2 /lib/x86_64-linux-gnu/libcares.so.2
COPY --from=build /lib/x86_64-linux-gnu/libnghttp2.so.14 /lib/x86_64-linux-gnu/libnghttp2.so.14
COPY --from=build /lib/x86_64-linux-gnu/libcrypto.so.3 /lib/x86_64-linux-gnu/libcrypto.so.3
COPY --from=build /lib/x86_64-linux-gnu/libssl.so.3 /lib/x86_64-linux-gnu/libssl.so.3
COPY --from=build /lib/x86_64-linux-gnu/libicui18n.so.72 /lib/x86_64-linux-gnu/libicui18n.so.72
COPY --from=build /lib/x86_64-linux-gnu/libicuuc.so.72 /lib/x86_64-linux-gnu/libicuuc.so.72
COPY --from=build /lib/x86_64-linux-gnu/libstdc++.so.6 /lib/x86_64-linux-gnu/libstdc++.so.6
COPY --from=build /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/libm.so.6
COPY --from=build /lib/x86_64-linux-gnu/libgcc_s.so.1 /lib/x86_64-linux-gnu/libgcc_s.so.1
COPY --from=build /lib/x86_64-linux-gnu/libpthread.so.0 /lib/x86_64-linux-gnu/libpthread.so.0
COPY --from=build /lib/x86_64-linux-gnu/libdl.so.2 /lib/x86_64-linux-gnu/libdl.so.2
COPY --from=build /lib/x86_64-linux-gnu/libbrotlicommon.so.1 /lib/x86_64-linux-gnu/libbrotlicommon.so.1
COPY --from=build /lib/x86_64-linux-gnu/libicudata.so.72 /lib/x86_64-linux-gnu/libicudata.so.72
COPY --from=build /lib/x86_64-linux-gnu/librt.so.1 /lib/x86_64-linux-gnu/librt.so.1
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
COPY --from=build /etc/ld.so.cache /etc/ld.so.cache

# Distro definition
COPY --from=build /etc/os-release /etc/os-release
COPY --from=build /usr/lib/os-release /usr/lib/os-release

# Node modules, including Puppeteer
COPY --from=build /src/node_modules /src/node_modules

# Puppeteer example
COPY pdf.js /src/pdf.js
