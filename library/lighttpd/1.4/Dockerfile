# lighttpd 1.4 rootfs for Unikraft bincompat. There is no official lighttpd
# image, so we `apk add` it into a build stage and copy the binary, its `ldd`
# libraries and the musl loader into a scratch image.
FROM alpine:3.21 AS build

RUN apk add --no-cache lighttpd

FROM scratch

# lighttpd binary
COPY --from=build /usr/sbin/lighttpd /usr/sbin/lighttpd

# musl loader and the shared libs reported by `ldd`
COPY --from=build /lib/ld-musl-x86_64.so.1   /lib/ld-musl-x86_64.so.1
COPY --from=build /lib/libc.musl-x86_64.so.1 /lib/libc.musl-x86_64.so.1
COPY --from=build /usr/lib/libcrypto.so.3    /usr/lib/libcrypto.so.3
COPY --from=build /usr/lib/libpcre2-8.so.0   /usr/lib/libpcre2-8.so.0

# user/group db and a writable temp dir for request bodies
COPY --from=build /etc/passwd /etc/passwd
COPY --from=build /etc/group  /etc/group
COPY --from=build /tmp        /tmp

# config + web root
COPY ./conf/lighttpd.conf /etc/lighttpd/lighttpd.conf
COPY ./wwwroot            /wwwroot
