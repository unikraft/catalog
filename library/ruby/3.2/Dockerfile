FROM --platform=linux/x86_64 ruby:3.2.2-bookworm AS build

FROM scratch

# Ruby binary
COPY --from=build /usr/local/bin/ruby /usr/bin/ruby

# Ruby libraries
COPY --from=build /usr/local/lib/ruby /usr/local/lib/ruby

# System libraries
COPY --from=build /usr/local/lib/libruby.so.3.2 /usr/local/lib/libruby.so.3.2
COPY --from=build /lib/x86_64-linux-gnu/libz.so.1 /lib/x86_64-linux-gnu/libz.so.1
COPY --from=build /lib/x86_64-linux-gnu/libgmp.so.10 /lib/x86_64-linux-gnu/libgmp.so.10
COPY --from=build /lib/x86_64-linux-gnu/libcrypt.so.1 /lib/x86_64-linux-gnu/libcrypt.so.1
COPY --from=build /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/libm.so.6
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=build /lib/x86_64-linux-gnu/libgcc_s.so.1 /lib/x86_64-linux-gnu/libgcc_s.so.1
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
COPY --from=build /etc/ld.so.cache /etc/ld.so.cache

# Simple Ruby HTTP server
COPY ./server.rb /src/server.rb
