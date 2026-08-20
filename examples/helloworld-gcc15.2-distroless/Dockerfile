FROM gcc:15.2.0-bookworm AS build

WORKDIR /src

COPY ./helloworld.c /src/helloworld.c

RUN set -xe; \
  gcc \
  -Wall -Wextra \
  -fPIC -pie \
  -o /helloworld helloworld.c

FROM gcr.io/distroless/cc-debian12@sha256:e5d81ddde149641e2a9ba55be4545bc125c67de07508b03ba4c22e6eb0ded5aa

COPY --from=build /helloworld /helloworld
