FROM rust:1.75.0-bookworm AS build

WORKDIR /src

COPY ./helloworld.rs /src/helloworld.rs

RUN set -xe; \
    rustc -o /helloworld /src/helloworld.rs

FROM gcr.io/distroless/cc-debian12@sha256:e5d81ddde149641e2a9ba55be4545bc125c67de07508b03ba4c22e6eb0ded5aa

COPY --from=build /helloworld /helloworld

