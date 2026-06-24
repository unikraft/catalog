ARG BASE=ghcr.io/hyperlight-dev/hyperlight-unikraft/nodejs-base:latest
FROM ${BASE} AS rootfs
COPY hello.js /app/hello.js

FROM alpine:3.20 AS cpio
RUN apk add --no-cache cpio findutils
COPY --from=rootfs / /rootfs/
RUN cd /rootfs && find . | cpio -o -H newc > /output.cpio 2>/dev/null
