# Use golang 1.21.3-bookworm as the base image
FROM golang:1.21.3-bookworm AS build

# Clone CoreDNS v1.11.1 repository
RUN git clone --branch v1.11.1 --depth 1 https://github.com/coredns/coredns.git /go/src/coredns

# Set working directory
WORKDIR /go/src/coredns

# Build CoreDNS with PIE
RUN set -xe; \
    CGO_ENABLED=1 \
    go build \
        -buildmode=pie \
        -ldflags "-linkmode external -extldflags '-static-pie'" \
	-tags netgo \
        -o /coredns \
        .

# Use scratch as the base image for minimalism
FROM scratch

# Copy CoreDNS binary and necessary libraries
COPY --from=build /coredns /coredns
COPY --from=build /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/

# Set the command to run CoreDNS
CMD ["/coredns"]

