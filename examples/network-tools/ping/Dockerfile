FROM debian:trixie-slim AS build

RUN apt-get update && apt-get install -y \
  inetutils-ping

FROM scratch

# Binary
COPY --from=build /usr/bin/ping /usr/bin/ping

# Library dependencies
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
