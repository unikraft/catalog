FROM rust:1.80.1-bookworm AS build

WORKDIR /src

RUN set -xe; \
    mkdir -p /target/etc; \
    apt-get update; \
    apt-get install -y --no-install-recommends \
      ca-certificates \
      tzdata \
      wget \
      xz-utils \
      musl-dev \
      musl-tools \
      patch \
      git; \
    git clone https://github.com/fbergen/findtime.git; \
    cd findtime; \
    git checkout f1c97c2; \
    ln -sf ../usr/share/zoneinfo/Etc/UTC /target/etc/localtime; \
    echo "Etc/UTC" > /target/etc/timezone;

WORKDIR /src/findtime

RUN set -xe; \
    rustup target add x86_64-unknown-linux-musl; \
    cargo build --release --target=x86_64-unknown-linux-musl \
    ;

FROM scratch

COPY --from=build /target/etc /etc
COPY --from=build /usr/share/zoneinfo/Etc/UTC /usr/share/zoneinfo/Etc/UTC
COPY --from=build /etc/ssl/certs/ca-certificates.crt /etc/ssl/certs/ca-certificates.crt
COPY --from=build /src/findtime/target/x86_64-unknown-linux-musl/release/findtime /findtime
COPY --from=build /src/findtime/index.html /src/findtime/main.js /
