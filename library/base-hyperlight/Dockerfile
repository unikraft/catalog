FROM alpine:3.20 AS fallback

RUN apk add --no-cache musl-dev gcc

COPY ./fallback.c /fallback.c

RUN set -xe; \
    gcc \
      -static-pie \
      -fPIE \
      -fno-stack-protector \
      -O3 \
      -Wall \
      -Wextra \
      -Wno-unused \
      -Wno-unused-parameter \
      -o /fallback \
      /fallback.c

FROM scratch

COPY --from=fallback /fallback /bin/fallback
