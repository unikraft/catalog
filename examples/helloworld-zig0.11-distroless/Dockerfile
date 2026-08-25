FROM gcc:13.2.0-bookworm AS zig

RUN set -xe; \
    apt-get update; \
    apt-get install -y --no-install-recommends \
      ca-certificates \
      curl \
      xz-utils; \
    rm -rf /var/lib/apt/lists/*

WORKDIR /zig

ARG ZIG_VERSION=0.11.0

RUN set -xe; \
    curl -o /zig.tar.xz \
      https://ziglang.org/download/${ZIG_VERSION}/zig-linux-$(uname -m)-${ZIG_VERSION}.tar.xz; \
    tar -xf /zig.tar.xz --strip-components 1 -C /zig; \
    mv /zig/zig /usr/bin/zig; \
    mv /zig/lib /usr/lib/zig; \
    rm -f /zig.tar.xz

FROM zig AS build

WORKDIR /src

COPY . /src

RUN set -xe; \
    zig build-exe /src/helloworld.zig \
      -target x86_64-linux-musl \
      -O ReleaseSmall \
      -fPIE \
      -static

FROM gcr.io/distroless/static-debian13

COPY --from=build /src/helloworld /helloworld

ENTRYPOINT ["/helloworld"]