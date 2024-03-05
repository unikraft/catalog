FROM rust:1.75.0-bookworm AS build

WORKDIR /src

COPY ./server.rs /src/server.rs

RUN set -xe; \
    rustc -o /server /src/server.rs

FROM scratch

COPY --from=build /server /server
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/
COPY --from=build /lib/x86_64-linux-gnu/libgcc_s.so.1 /lib/x86_64-linux-gnu/
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/
