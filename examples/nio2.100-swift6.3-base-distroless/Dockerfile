FROM swift:6.3-bookworm AS build

WORKDIR /app
COPY Package.swift .
COPY Sources ./Sources

RUN swift build -c release --static-swift-stdlib

FROM gcr.io/distroless/cc-debian12@sha256:e5d81ddde149641e2a9ba55be4545bc125c67de07508b03ba4c22e6eb0ded5aa

COPY --from=build /app/.build/release/swift-http /server

