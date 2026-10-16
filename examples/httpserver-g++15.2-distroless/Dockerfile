FROM gcc:15.2.0-bookworm AS build

WORKDIR /src

COPY ./http_server.cpp /src/http_server.cpp

RUN set -xe; \
  g++ \
  -Wall -Wextra \
  -fPIC -pie \
  -o /http_server http_server.cpp

FROM gcr.io/distroless/cc-debian13@sha256:9b615fff20e1a4fad29c2b30562580b212c7dd5e2225236735cca0070ed11c78

# C++ HTTP server
COPY --from=build /http_server /http_server
