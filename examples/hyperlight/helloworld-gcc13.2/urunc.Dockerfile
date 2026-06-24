FROM alpine:3.20 AS build
RUN apk add --no-cache musl-dev gcc cpio findutils
COPY hello.c /src/hello.c
RUN gcc -static-pie -fPIE -fno-stack-protector -o /src/hello /src/hello.c
RUN mkdir -p /rootfs/bin && cp /src/hello /rootfs/bin/hello \
    && cd /rootfs && find . | cpio -o -H newc > /output.cpio 2>/dev/null

FROM scratch
COPY .unikraft/build/helloworld-hyperlight_hyperlight-x86_64 /unikernel/kernel
COPY --from=build /output.cpio /unikernel/initrd.cpio
COPY urunc.json /urunc.json
LABEL "com.urunc.unikernel.unikernelType"="unikraft"
LABEL "com.urunc.unikernel.hypervisor"="hyperlight"
LABEL "com.urunc.unikernel.binary"="/unikernel/kernel"
LABEL "com.urunc.unikernel.initrd"="/unikernel/initrd.cpio"
