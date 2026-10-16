FROM alpine:3.21 AS builder

RUN apk add --no-cache gcc musl-dev

WORKDIR /app

COPY src/main.c .

RUN gcc \
    -O2 \
    -fPIE \
    -static-pie \
    -pthread \
    -o /task-runner \
    main.c

FROM gcr.io/distroless/static-debian12

COPY --from=builder /task-runner /usr/bin/task-runner

ENTRYPOINT ["/usr/bin/task-runner"]