FROM debian:bookworm AS build 

FROM scratch

# Binaries
COPY --from=build /usr/bin/ls /usr/bin/ls 
COPY --from=build /usr/bin/cat /usr/bin/cat  
COPY --from=build /usr/bin/pwd /usr/bin/pwd
COPY --from=build /usr/bin/uniq /usr/bin/uniq
COPY --from=build /usr/bin/sort /usr/bin/sort

# Library dependencies
COPY --from=build /lib/x86_64-linux-gnu/libselinux.so.1 /lib/x86_64-linux-gnu/libselinux.so.1
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=build /lib/x86_64-linux-gnu/libpcre2-8.so.0 /lib/x86_64-linux-gnu/libpcre2-8.so.0
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
COPY --from=build /etc/ld.so.cache /etc/ld.so.cache

# Test files
COPY ./test-files/ /test-files/
