FROM debian:bookworm AS build

RUN set -xe; \
    apt update; \
    apt install -y --no-install-recommends \
      nodejs \
    ;

FROM scratch

# Node binary
COPY --from=build /usr/bin/node /usr/bin/node

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
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
COPY --from=build /etc/ld.so.cache /etc/ld.so.cache

# Distro definition
COPY --from=build /etc/os-release /etc/os-release
COPY --from=build /usr/lib/os-release /usr/lib/os-release

# Node HTTP server
COPY ./server.js /usr/src/server.js
