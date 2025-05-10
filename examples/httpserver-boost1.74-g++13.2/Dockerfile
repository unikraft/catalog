FROM --platform=linux/x86_64 debian:bookworm AS build

RUN set -xe ; \
	apt -yqq update ; \
	apt -yqq install build-essential ; \
	apt -yqq install libboost-all-dev

WORKDIR /src

COPY ./http_server.cpp /src/http_server.cpp

RUN set -xe; \
    g++ \
	-Wall -Wextra \
	-fPIC -pie \
	-o /http_server http_server.cpp \
	-lboost_system -lboost_thread -lpthread

FROM scratch

# System / C++ libraries
COPY --from=build /lib/x86_64-linux-gnu/libboost_thread.so.1.74.0 /lib/x86_64-linux-gnu/libboost_thread.so.1.74.0
COPY --from=build /lib/x86_64-linux-gnu/libstdc++.so.6 /lib/x86_64-linux-gnu/libstdc++.so.6
COPY --from=build /lib/x86_64-linux-gnu/libgcc_s.so.1 /lib/x86_64-linux-gnu/libgcc_s.so.1
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=build /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/libm.so.6
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2

# C++ HTTP server
COPY --from=build /http_server /http_server
