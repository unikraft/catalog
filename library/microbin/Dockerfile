FROM rust:bookworm AS builder

RUN apt-get update && apt-get install -y --no-install-recommends \
    musl-tools \
    ca-certificates \
    tzdata \
    && rm -rf /var/lib/apt/lists/*

RUN rustup target add x86_64-unknown-linux-musl

WORKDIR /src

RUN wget -q "https://github.com/szabodanika/microbin/archive/refs/tags/v2.0.4.tar.gz" && \
    tar -xzf v2.0.4.tar.gz && \
    mv microbin-2.0.4/* . && \
    rm -f v2.0.4.tar.gz

ENV CFLAGS="-std=gnu99 -Wno-error=incompatible-pointer-types -w -DSQLITE_TEMP_STORE=3"
ENV TMPDIR="/src/tmp"
RUN mkdir -p /src/tmp

RUN cargo update -p libc && cargo update -p getrandom && \
    RUSTFLAGS="-C target-feature=+crt-static -C relocation-model=pie" \
    cargo build --release --target x86_64-unknown-linux-musl && \
    rm -rf /src/tmp

FROM scratch

COPY --from=builder /etc/ssl/certs/ca-certificates.crt /etc/ssl/certs/ca-certificates.crt
COPY --from=builder /usr/share/zoneinfo/Etc/UTC /usr/share/zoneinfo/Etc/UTC
COPY --from=builder /usr/share/zoneinfo/Etc/UTC /etc/localtime

COPY --from=builder /src/target/x86_64-unknown-linux-musl/release/microbin /microbin