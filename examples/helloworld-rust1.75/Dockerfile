FROM rust:1.75.0-bookworm AS build

WORKDIR /src

COPY ./helloworld.rs /src/helloworld.rs

RUN set -xe; \
    rustc -o /helloworld /src/helloworld.rs

FROM scratch

COPY --from=build /helloworld /helloworld
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/
COPY --from=build /lib/x86_64-linux-gnu/libgcc_s.so.1 /lib/x86_64-linux-gnu/
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/
