FROM gcc:13.2.0 AS fallback

COPY ./fallback.c /fallback.c

RUN set -xe; \
    gcc \
      -fPIC \
      -g \
      -o /fallback \
      -O3 \
      -static-pie \
      -Wall \
      -Wextra \
      -Wno-unused \
      -Wno-unused-parameter \
      /fallback.c

FROM scratch

COPY --from=fallback /fallback /fallback
