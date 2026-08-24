FROM gcc:15.2-bookworm AS build

WORKDIR /src

COPY ./http_server.c /src/http_server.c

RUN set -xe; \
  gcc \
  -Wall -Wextra \
  -fPIC -pie \
  -o /http_server http_server.c

FROM gcr.io/distroless/cc-debian12@sha256:e5d81ddde149641e2a9ba55be4545bc125c67de07508b03ba4c22e6eb0ded5aa

COPY --from=build /http_server /http_server
