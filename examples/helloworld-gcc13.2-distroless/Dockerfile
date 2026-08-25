FROM gcc:13.2.0-bookworm AS build

WORKDIR /src

COPY ./helloworld.c /src/helloworld.c

RUN set -xe; \
    gcc \
    -Wall -Wextra \
    -fPIC -pie \
    -o /helloworld helloworld.c

FROM gcr.io/distroless/cc-debian13:latest

COPY --from=build /helloworld /helloworld