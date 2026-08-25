FROM --platform=linux/x86_64 debian:bookworm AS build

RUN set -xe ; \
	apt -yqq update ; \
	apt -yqq install build-essential ; \
	apt -yqq install libboost-all-dev

WORKDIR /src

COPY ./http_server.cpp /src/http_server.cpp

RUN set -xe; \
    g++ \
        -O3 \
	      -Wall -Wextra \
	      -fPIC -pie \
	      -o /http_server http_server.cpp \
	      -lboost_system -lboost_thread -lpthread

FROM gcr.io/distroless/cc-debian12@sha256:e5d81ddde149641e2a9ba55be4545bc125c67de07508b03ba4c22e6eb0ded5aa

# Boost dependency
COPY --from=build /lib/x86_64-linux-gnu/libboost_thread.so.1.74.0 /lib/x86_64-linux-gnu/libboost_thread.so.1.74.0

# C++ HTTP server
COPY --from=build /http_server /http_server

