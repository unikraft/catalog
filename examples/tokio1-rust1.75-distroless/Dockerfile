FROM rust:1.75.0-bookworm AS build

WORKDIR /src

COPY ./src /src/src
COPY ./Cargo.toml /src/Cargo.toml
COPY ./Cargo.lock /src/Cargo.lock

RUN cargo build --release --locked

FROM gcr.io/distroless/cc-debian12@sha256:e5d81ddde149641e2a9ba55be4545bc125c67de07508b03ba4c22e6eb0ded5aa

COPY --from=build /src/target/release/http-tokio /server

