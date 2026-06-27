FROM gcc:15.2.0-bookworm AS build

WORKDIR /src

COPY ./helloworld.cpp /src/helloworld.cpp

RUN set -xe; \
    g++ \
	-Wall -Wextra \
	-fPIC -pie \
	-o /helloworld helloworld.cpp

FROM scratch

# System / C++ libraries
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/
COPY --from=build /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/libm.so.6
COPY --from=build /usr/local/lib64/libgcc_s.so.1 /usr/local/lib64/libgcc_s.so.1
COPY --from=build /usr/local/lib64/libstdc++.so.6 /usr/local/lib64/libstdc++.so.6
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
COPY --from=build /etc/ld.so.cache /etc/ld.so.cache

# C++ HTTP server
COPY --from=build /helloworld /helloworld
