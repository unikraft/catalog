FROM alpine:3.20 AS build
RUN apk add --no-cache musl-dev gcc
COPY hello.c /src/hello.c
RUN gcc -static-pie -fPIE -fno-stack-protector -Os -o /src/hello /src/hello.c

FROM alpine:3.20 AS cpio
RUN apk add --no-cache cpio findutils
RUN mkdir -p /rootfs/bin
COPY --from=build /src/hello /rootfs/bin/hello
RUN cd /rootfs && find . | cpio -o -H newc > /output.cpio 2>/dev/null
