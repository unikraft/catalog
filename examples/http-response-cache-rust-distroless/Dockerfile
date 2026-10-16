FROM rust:1.89 AS builder

WORKDIR /app

COPY src/main.rs .

RUN mkdir -p /out

RUN rustc \
    --edition=2021 \
    -C opt-level=3 \
    -C target-feature=+crt-static \
    -o /out/http-response-cache \
    main.rs

FROM gcr.io/distroless/static-debian12

COPY --from=builder /out/http-response-cache /usr/bin/http-response-cache

EXPOSE 8080

ENTRYPOINT ["/usr/bin/http-response-cache"]