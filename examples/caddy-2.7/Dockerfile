FROM --platform=linux/x86_64 golang:1.21.4-bookworm AS build

# Inspired from: https://github.com/caddyserver/caddy-docker/blob/master/2.7/builder/Dockerfile

RUN set -xe; apt-get update ; \
    apt-get install -y --no-install-recommends \
    ca-certificates \
    git \
    libcap2-bin \
    ;

ENV XCADDY_VERSION v0.3.5
# Configures xcaddy to build with this version of Caddy
ENV CADDY_VERSION v2.7.5
# Configures xcaddy to not clean up post-build (unnecessary in a container)
ENV XCADDY_SKIP_CLEANUP 1
# Sets capabilities for output caddy binary to be able to bind to privileged ports
ENV XCADDY_SETCAP 1

RUN set -xe; \
    wget -O /tmp/xcaddy.tar.gz "https://github.com/caddyserver/xcaddy/releases/download/v0.3.5/xcaddy_0.3.5_linux_amd64.tar.gz"; \
    tar x -z -f /tmp/xcaddy.tar.gz -C /usr/bin xcaddy; \
    rm -f /tmp/xcaddy.tar.gz; \
    chmod +x /usr/bin/xcaddy;

ENV CGO_ENABLED=1
ENV XCADDY_GO_BUILD_FLAGS "-buildmode=pie -ldflags '-linkmode external -extldflags -static-pie'"

RUN /usr/bin/xcaddy build

FROM scratch

COPY --from=build /go/caddy /usr/local/bin/caddy
COPY Caddyfile /etc/caddy/Caddyfile
