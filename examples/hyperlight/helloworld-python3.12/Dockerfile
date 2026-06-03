# Python hello world on Hyperlight
#
# Extends the Python base runtime with user code.
# The base image contains CPython + stdlib; this just adds the script.
#
# For local builds without GHCR, build the base first:
#   docker build -f ../../runtimes/python.Dockerfile -t python-base ../../runtimes
# Then:
#   docker build --build-arg BASE=python-base --target cpio -t python-cpio .

ARG BASE=ghcr.io/hyperlight-dev/hyperlight-unikraft/python-base:latest
FROM ${BASE} AS rootfs
COPY hello.py /hello.py

# --- CPIO rootfs builder ---
FROM alpine:3.20 AS cpio
RUN apk add --no-cache cpio findutils
COPY --from=rootfs / /rootfs/
RUN cd /rootfs && find . | cpio -o -H newc > /output.cpio 2>/dev/null
