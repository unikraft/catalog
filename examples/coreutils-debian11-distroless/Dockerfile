FROM debian:bookworm AS build

# Base Ditroless image (containing libc and linkers)
FROM gcr.io/distroless/cc-debian12@sha256:e5d81ddde149641e2a9ba55be4545bc125c67de07508b03ba4c22e6eb0ded5aa

# Binaries
COPY --from=build /usr/bin/ls /usr/bin/ls
COPY --from=build /usr/bin/cat /usr/bin/cat
COPY --from=build /usr/bin/pwd /usr/bin/pwd
COPY --from=build /usr/bin/uniq /usr/bin/uniq
COPY --from=build /usr/bin/sort /usr/bin/sort

# Remaining library dependencies
COPY --from=build /lib/x86_64-linux-gnu/libselinux.so.1 /lib/x86_64-linux-gnu/libselinux.so.1
COPY --from=build /lib/x86_64-linux-gnu/libpcre2-8.so.0 /lib/x86_64-linux-gnu/libpcre2-8.so.0

# Test files
COPY ./test-files/ /test-files/

