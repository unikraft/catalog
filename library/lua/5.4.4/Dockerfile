FROM debian:bookworm AS build

ARG LUA_VERSION=5.4

RUN set -xe; \
    apt update; \
    apt install -y --no-install-recommends \
      lua${LUA_VERSION} \
      liblua${LUA_VERSION}-dev \
      luarocks \
      libssl-dev \
      build-essential \
      m4 \
    ;

RUN set -xe ; \
    luarocks --lua-version ${LUA_VERSION} install luasocket ; \
    luarocks --lua-version ${LUA_VERSION} install http

FROM scratch

ARG LUA_VERSION=5.4

# Lua binary
COPY --from=build /usr/bin/lua${LUA_VERSION} /usr/bin/lua

# Lua libraries
COPY --from=build /usr/local/lib/lua/5.4 /usr/local/lib/lua/5.4
COPY --from=build /usr/local/share/lua/5.4 /usr/local/share/lua/5.4
COPY --from=build /usr/share/lua/5.4 /usr/share/lua/5.4

# System libraries

COPY --from=build /lib/x86_64-linux-gnu/libreadline.so.8 /lib/x86_64-linux-gnu/libreadline.so.8
COPY --from=build /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/libm.so.6
COPY --from=build /lib/x86_64-linux-gnu/libdl.so.2 /lib/x86_64-linux-gnu/libdl.so.2
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=build /lib/x86_64-linux-gnu/libtinfo.so.6 /lib/x86_64-linux-gnu/libtinfo.so.6
COPY --from=build /lib/x86_64-linux-gnu/libssl.so.3 /lib/x86_64-linux-gnu/libssl.so.3
COPY --from=build /lib/x86_64-linux-gnu/libcrypto.so.3 /lib/x86_64-linux-gnu/libcrypto.so.3
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
COPY --from=build /etc/ld.so.cache /etc/ld.so.cache

# Lua server
COPY ./server.lua /src/server.lua
