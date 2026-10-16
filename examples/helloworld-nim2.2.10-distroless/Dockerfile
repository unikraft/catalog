FROM nim:2.2.10 AS builder

WORKDIR /usr/src/app

COPY src/main.nim .

RUN nim c \
    -d:release \
    --passC:-fPIE \
    --passL:-static-pie \
    -o:/out/hello \
    main.nim

FROM scratch

COPY --from=builder /out/hello /usr/bin/hello