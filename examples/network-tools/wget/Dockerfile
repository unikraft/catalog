FROM alpine:3.20.3 AS build

RUN apk add --no-cache \
    wget

FROM scratch

# Binary
COPY --from=build /usr/bin/wget /usr/bin/wget

# Library dependencies
COPY --from=build /etc/ssl /etc/ssl
COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=build /usr/lib/libpcre2-8.so.0 /usr/lib/libpcre2-8.so.0
COPY --from=build /usr/lib/libidn2.so.0 /usr/lib/libidn2.so.0
COPY --from=build /lib/libssl.so.3 /lib/libssl.so.3
COPY --from=build /lib/libcrypto.so.3 /lib/libcrypto.so.3
COPY --from=build /lib/libz.so.1 /lib/libz.so.1
COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=build /usr/lib/libunistring.so.5 /usr/lib/libunistring.so.5
