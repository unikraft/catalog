FROM alpine/curl-http3:8.11.0 AS curl-http3

FROM scratch

COPY --from=curl-http3 /usr/local/bin/curl /usr/local/bin/curl

COPY --from=curl-http3 /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=curl-http3 /usr/local/lib/libcurl.so.4 /usr/local/lib/libcurl.so.4
COPY --from=curl-http3 /lib/libz.so.1 /lib/libz.so.1
COPY --from=curl-http3 /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=curl-http3 /usr/lib/libnghttp2.so.14 /usr/lib/libnghttp2.so.14
COPY --from=curl-http3 /usr/lib/libidn2.so.0 /usr/lib/libidn2.so.0
COPY --from=curl-http3 /usr/lib/libpsl.so.5 /usr/lib/libpsl.so.5
COPY --from=curl-http3 /usr/lib/libbrotlidec.so.1 /usr/lib/libbrotlidec.so.1
COPY --from=curl-http3 /usr/lib/libgcc_s.so.1 /usr/lib/libgcc_s.so.1
COPY --from=curl-http3 /usr/lib/libunistring.so.5 /usr/lib/libunistring.so.5
COPY --from=curl-http3 /usr/lib/libbrotlicommon.so.1 /usr/lib/libbrotlicommon.so.1
