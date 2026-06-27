ARG BASE=ghcr.io/hyperlight-dev/hyperlight-unikraft/python-base:latest
FROM ${BASE} AS rootfs
COPY test_tools.py /test_tools.py
# hyperlight.py is the guest-side SDK test_tools.py imports. Python's
# default sys.path includes the directory of the script, so placing
# hyperlight.py at / alongside test_tools.py is enough.
COPY hyperlight.py /hyperlight.py

FROM alpine:3.20 AS cpio
RUN apk add --no-cache cpio findutils
COPY --from=rootfs / /rootfs/
RUN cd /rootfs && find . | cpio -o -H newc > /output.cpio 2>/dev/null
