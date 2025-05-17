FROM debian:trixie-slim AS build

RUN apt-get update && apt-get install -y \
  dnsutils

FROM scratch

# Binary
COPY --from=build /usr/bin/nslookup /usr/bin/nslookup

# Library dependencies
COPY --from=build /lib/x86_64-linux-gnu/libjemalloc.so.2 /lib/x86_64-linux-gnu/libjemalloc.so.2
COPY --from=build /lib/x86_64-linux-gnu/libisc-9.20.3-1-Debian.so /lib/x86_64-linux-gnu/libisc-9.20.3-1-Debian.so
COPY --from=build /lib/x86_64-linux-gnu/libdns-9.20.3-1-Debian.so /lib/x86_64-linux-gnu/libdns-9.20.3-1-Debian.so
COPY --from=build /lib/x86_64-linux-gnu/libisccfg-9.20.3-1-Debian.so /lib/x86_64-linux-gnu/libisccfg-9.20.3-1-Debian.so
COPY --from=build /lib/x86_64-linux-gnu/libidn2.so.0 /lib/x86_64-linux-gnu/libidn2.so.0
COPY --from=build /lib/x86_64-linux-gnu/libedit.so.2 /lib/x86_64-linux-gnu/libedit.so.2
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=build /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/libm.so.6
COPY --from=build /lib/x86_64-linux-gnu/libstdc++.so.6 /lib/x86_64-linux-gnu/libstdc++.so.6
COPY --from=build /lib/x86_64-linux-gnu/libgcc_s.so.1 /lib/x86_64-linux-gnu/libgcc_s.so.1
COPY --from=build /lib/x86_64-linux-gnu/libuv.so.1 /lib/x86_64-linux-gnu/libuv.so.1
COPY --from=build /lib/x86_64-linux-gnu/libssl.so.3 /lib/x86_64-linux-gnu/libssl.so.3
COPY --from=build /lib/x86_64-linux-gnu/libcrypto.so.3 /lib/x86_64-linux-gnu/libcrypto.so.3
COPY --from=build /lib/x86_64-linux-gnu/libz.so.1 /lib/x86_64-linux-gnu/libz.so.1
COPY --from=build /lib/x86_64-linux-gnu/libjson-c.so.5 /lib/x86_64-linux-gnu/libjson-c.so.5
COPY --from=build /lib/x86_64-linux-gnu/libnghttp2.so.14 /lib/x86_64-linux-gnu/libnghttp2.so.14
COPY --from=build /lib/x86_64-linux-gnu/libxml2.so.2 /lib/x86_64-linux-gnu/libxml2.so.2
COPY --from=build /lib/x86_64-linux-gnu/liburcu.so.8 /lib/x86_64-linux-gnu/liburcu.so.8
COPY --from=build /lib/x86_64-linux-gnu/liburcu-common.so.8 /lib/x86_64-linux-gnu/liburcu-common.so.8
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
COPY --from=build /lib/x86_64-linux-gnu/libgssapi_krb5.so.2 /lib/x86_64-linux-gnu/libgssapi_krb5.so.2
COPY --from=build /lib/x86_64-linux-gnu/libkrb5.so.3 /lib/x86_64-linux-gnu/libkrb5.so.3
COPY --from=build /lib/x86_64-linux-gnu/libmaxminddb.so.0 /lib/x86_64-linux-gnu/libmaxminddb.so.0
COPY --from=build /lib/x86_64-linux-gnu/libfstrm.so.0 /lib/x86_64-linux-gnu/libfstrm.so.0
COPY --from=build /lib/x86_64-linux-gnu/libprotobuf-c.so.1 /lib/x86_64-linux-gnu/libprotobuf-c.so.1
COPY --from=build /lib/x86_64-linux-gnu/liblmdb.so.0 /lib/x86_64-linux-gnu/liblmdb.so.0
COPY --from=build /lib/x86_64-linux-gnu/liburcu-cds.so.8 /lib/x86_64-linux-gnu/liburcu-cds.so.8
COPY --from=build /lib/x86_64-linux-gnu/libns-9.20.3-1-Debian.so /lib/x86_64-linux-gnu/libns-9.20.3-1-Debian.so
COPY --from=build /lib/x86_64-linux-gnu/libunistring.so.5 /lib/x86_64-linux-gnu/libunistring.so.5
COPY --from=build /lib/x86_64-linux-gnu/libtinfo.so.6 /lib/x86_64-linux-gnu/libtinfo.so.6
COPY --from=build /lib/x86_64-linux-gnu/libbsd.so.0 /lib/x86_64-linux-gnu/libbsd.so.0
COPY --from=build /lib/x86_64-linux-gnu/libzstd.so.1 /lib/x86_64-linux-gnu/libzstd.so.1
COPY --from=build /lib/x86_64-linux-gnu/libicuuc.so.72 /lib/x86_64-linux-gnu/libicuuc.so.72
COPY --from=build /lib/x86_64-linux-gnu/liblzma.so.5 /lib/x86_64-linux-gnu/liblzma.so.5
COPY --from=build /lib/x86_64-linux-gnu/libk5crypto.so.3 /lib/x86_64-linux-gnu/libk5crypto.so.3
COPY --from=build /lib/x86_64-linux-gnu/libcom_err.so.2 /lib/x86_64-linux-gnu/libcom_err.so.2
COPY --from=build /lib/x86_64-linux-gnu/libkrb5support.so.0 /lib/x86_64-linux-gnu/libkrb5support.so.0
COPY --from=build /lib/x86_64-linux-gnu/libkeyutils.so.1 /lib/x86_64-linux-gnu/libkeyutils.so.1
COPY --from=build /lib/x86_64-linux-gnu/libresolv.so.2 /lib/x86_64-linux-gnu/libresolv.so.2
COPY --from=build /lib/x86_64-linux-gnu/libmd.so.0 /lib/x86_64-linux-gnu/libmd.so.0
COPY --from=build /lib/x86_64-linux-gnu/libicudata.so.72 /lib/x86_64-linux-gnu/libicudata.so.72
