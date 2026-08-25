FROM gcc:13.2.0-bookworm AS build

WORKDIR /src

COPY ./http_server.c /src/http_server.c

RUN set -xe; \
    gcc \
    -Wall -Wextra \
    -fPIC -pie \
    -o /http_server http_server.c

FROM gcr.io/distroless/cc-debian13:latest

COPY --from=build /http_server /http_server