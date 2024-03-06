FROM rust:1.75.0-bookworm AS build

RUN cargo new --bin app
WORKDIR /app
COPY Cargo.toml ./
COPY src ./src
RUN cargo build --release

FROM scratch

COPY --from=build /app/target/release/hello /server
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/
COPY --from=build /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/
COPY --from=build /lib/x86_64-linux-gnu/libgcc_s.so.1 /lib/x86_64-linux-gnu/
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/
