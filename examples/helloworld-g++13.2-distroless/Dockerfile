FROM gcc:13.2.0-bookworm AS build

WORKDIR /src

COPY ./helloworld.cpp /src/helloworld.cpp

RUN set -xe; \
    g++ \
    -Wall -Wextra \
    -fPIC -pie \
    -o /helloworld helloworld.cpp

FROM gcr.io/distroless/cc-debian13

COPY --from=build /helloworld /helloworld