FROM --platform=linux/x86_64 ruby:3.2.2-bookworm AS build

FROM gcr.io/distroless/cc-debian12@sha256:e5d81ddde149641e2a9ba55be4545bc125c67de07508b03ba4c22e6eb0ded5aa

# Ruby binary
COPY --from=build /usr/local/bin/ruby /usr/bin/ruby

# Ruby libraries
COPY --from=build /usr/local/lib/ruby /usr/local/lib/ruby

# System libraries
COPY --from=build /usr/local/lib/libruby.so.3.2 /usr/local/lib/libruby.so.3.2
COPY --from=build /lib/x86_64-linux-gnu/libz.so.1 /lib/x86_64-linux-gnu/libz.so.1
COPY --from=build /lib/x86_64-linux-gnu/libgmp.so.10 /lib/x86_64-linux-gnu/libgmp.so.10
COPY --from=build /lib/x86_64-linux-gnu/libcrypt.so.1 /lib/x86_64-linux-gnu/libcrypt.so.1

# Simple Ruby HTTP server
COPY ./server.rb /src/server.rb
