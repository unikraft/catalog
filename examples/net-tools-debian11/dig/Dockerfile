FROM alpine:3.20.3 AS build

RUN apk add --no-cache \
    bind-tools

FROM scratch

# Binary
COPY --from=build /usr/bin/dig /usr/bin/dig

# Library dependencies
COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=build /usr/lib/libisc-9.18.31.so /usr/lib/libisc-9.18.31.so
COPY --from=build /usr/lib/libdns-9.18.31.so /usr/lib/libdns-9.18.31.so
COPY --from=build /usr/lib/libisccfg-9.18.31.so /usr/lib/libisccfg-9.18.31.so
COPY --from=build /usr/lib/libirs-9.18.31.so /usr/lib/libirs-9.18.31.so
COPY --from=build /usr/lib/libbind9-9.18.31.so /usr/lib/libbind9-9.18.31.so
COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=build /usr/lib/libuv.so.1 /usr/lib/libuv.so.1
COPY --from=build /lib/libssl.so.3 /lib/libssl.so.3
COPY --from=build /lib/libcrypto.so.3 /lib/libcrypto.so.3
COPY --from=build /lib/libz.so.1 /lib/libz.so.1
COPY --from=build /usr/lib/libjson-c.so.5 /usr/lib/libjson-c.so.5
COPY --from=build /usr/lib/libnghttp2.so.14 /usr/lib/libnghttp2.so.14
COPY --from=build /usr/lib/libxml2.so.2 /usr/lib/libxml2.so.2
COPY --from=build /usr/lib/libgssapi_krb5.so.2 /usr/lib/libgssapi_krb5.so.2
COPY --from=build /usr/lib/libkrb5.so.3 /usr/lib/libkrb5.so.3
COPY --from=build /usr/lib/libfstrm.so.0 /usr/lib/libfstrm.so.0
COPY --from=build /usr/lib/libprotobuf-c.so.1 /usr/lib/libprotobuf-c.so.1
COPY --from=build /usr/lib/libns-9.18.31.so /usr/lib/libns-9.18.31.so
COPY --from=build /usr/lib/liblzma.so.5 /usr/lib/liblzma.so.5
COPY --from=build /usr/lib/libk5crypto.so.3 /usr/lib/libk5crypto.so.3
COPY --from=build /lib/libcom_err.so.2 /lib/libcom_err.so.2
COPY --from=build /usr/lib/libkrb5support.so.0 /usr/lib/libkrb5support.so.0
COPY --from=build /usr/lib/libkeyutils.so.1 /usr/lib/libkeyutils.so.1
