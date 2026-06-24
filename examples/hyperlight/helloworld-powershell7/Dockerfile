ARG BASE=ghcr.io/hyperlight-dev/hyperlight-unikraft/powershell-base:latest
FROM ${BASE} AS rootfs
COPY hello.ps1 /scripts/hello.ps1

FROM alpine:3.20 AS cpio
RUN apk add --no-cache cpio findutils
COPY --from=rootfs / /rootfs/
# LIBDEVFS_AUTOMOUNT mkdirs /dev at boot; cpiovfs is read-only, so the
# directory has to exist inside the CPIO image or the mount call fails
# with EROFS and init_table aborts the kernel before powershell runs.
RUN mkdir -p /rootfs/dev
RUN cd /rootfs && find . | cpio -o -H newc > /output.cpio 2>/dev/null
