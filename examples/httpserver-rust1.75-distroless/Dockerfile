FROM rust:1.75.0-bookworm AS build

WORKDIR /src

COPY ./server.rs /src/server.rs

RUN set -xe; \
    rustc -O -o /server /src/server.rs

FROM gcr.io/distroless/cc-debian12@sha256:e5d81ddde149641e2a9ba55be4545bc125c67de07508b03ba4c22e6eb0ded5aa

COPY --from=build /server /server

