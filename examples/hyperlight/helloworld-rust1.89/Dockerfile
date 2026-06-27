FROM rust:1.89-alpine AS build
RUN apk add --no-cache musl-dev
COPY hello.rs /src/hello.rs
# On alpine, the default target is already x86_64-unknown-linux-musl.
# Using -C relocation-model=pie produces a static-pie binary.
RUN rustc -C target-feature=+crt-static -C relocation-model=pie -o /src/hello /src/hello.rs

FROM scratch AS rootfs
COPY --from=build /src/hello /bin/hello

# --- CPIO rootfs builder (used by: docker build --target cpio) ---
FROM alpine:3.20 AS cpio
RUN apk add --no-cache cpio findutils
COPY --from=rootfs / /rootfs/
RUN cd /rootfs && find . | cpio -o -H newc > /output.cpio 2>/dev/null
