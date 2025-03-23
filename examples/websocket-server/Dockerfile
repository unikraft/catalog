FROM gcc:13.2.0-bookworm AS build
WORKDIR /src
COPY ./websocket.c /src/websocket.c
# Get SHA1 implementation
RUN curl -O https://raw.githubusercontent.com/clibs/sha1/master/sha1.c \
    && curl -O https://raw.githubusercontent.com/clibs/sha1/master/sha1.h
RUN set -xe; \
    gcc \
    -Wall -Wextra \
    -fPIC -pie \
    -o /websocket_server websocket.c sha1.c

FROM scratch
COPY --from=build /websocket_server /websocket_server
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/
COPY --from=build /lib/x86_64-linux-gnu/libpthread.so.0 /lib/x86_64-linux-gnu/
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/
