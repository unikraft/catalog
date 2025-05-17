FROM alpine:3.20.3 AS build

RUN apk add --no-cache \
    mtr=0.95-r2

FROM scratch

# Binary
COPY --from=build /usr/sbin/mtr /usr/sbin/mtr
COPY --from=build /usr/sbin/mtr-packet /usr/sbin/mtr-packet

# Library dependencies
COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=build /usr/lib/libjansson.so.4 /usr/lib/libjansson.so.4
COPY --from=build /usr/lib/libncursesw.so.6 /usr/lib/libncursesw.so.6
COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
