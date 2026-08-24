FROM rust:1.90.0-bookworm AS build

RUN cargo new --bin app
WORKDIR /app
COPY Cargo.toml ./
COPY Cargo.lock ./
COPY src ./src
RUN cargo build --release --locked

FROM gcr.io/distroless/cc-debian12@sha256:e5d81ddde149641e2a9ba55be4545bc125c67de07508b03ba4c22e6eb0ded5aa

COPY ./Rocket.toml /Rocket.toml
COPY --from=build /app/target/release/hello /server

