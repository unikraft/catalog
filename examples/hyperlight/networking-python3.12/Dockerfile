# Networking Python example on Hyperlight
#
# Extends the Python base runtime with networking test scripts
# and DNS configuration.

ARG BASE=ghcr.io/hyperlight-dev/hyperlight-unikraft/python-base:latest
FROM ${BASE} AS rootfs
COPY http_get.py /http_get.py
COPY echo_server.py /echo_server.py
COPY urllib_get.py /urllib_get.py
COPY https_test.py /https_test.py
COPY echo_server_test.py /echo_server_test.py

# --- CPIO rootfs builder ---
FROM alpine:3.20 AS cpio
RUN apk add --no-cache cpio findutils ca-certificates
COPY --from=rootfs / /rootfs/

# DNS configuration for glibc's getaddrinfo (added in the cpio stage
# because the python-base image has no shell)
RUN mkdir -p /rootfs/etc && \
    echo "nameserver 8.8.8.8" > /rootfs/etc/resolv.conf && \
    echo "nameserver 8.8.4.4" >> /rootfs/etc/resolv.conf && \
    echo "hosts: files dns" > /rootfs/etc/nsswitch.conf && \
    echo "127.0.0.1 localhost" > /rootfs/etc/hosts

# CA certificates for TLS
RUN mkdir -p /rootfs/etc/ssl/certs /rootfs/usr/lib/ssl && \
    cp /etc/ssl/certs/ca-certificates.crt /rootfs/etc/ssl/certs/ && \
    ln -sf /etc/ssl/certs/ca-certificates.crt /rootfs/usr/lib/ssl/cert.pem

RUN cd /rootfs && find . | cpio -o -H newc > /output.cpio 2>/dev/null
