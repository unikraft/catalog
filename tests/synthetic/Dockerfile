FROM gcc:13.2.0-bookworm AS build

WORKDIR /src

COPY ./barrier /src/barrier
COPY ./dir /src/dir
COPY ./open /src/open
COPY ./socket /src/socket
COPY ./stat /src/stat
COPY ./sysconf /src/sysconf
COPY ./utils /src/utils
COPY ./Makefile /src

RUN make

FROM scratch

# Binaries
COPY --from=build /src/barrier/barrier /barrier
COPY --from=build /src/dir/dir /dir
COPY --from=build /src/dir/rootfs /rootfs
COPY --from=build /src/open/open /open
COPY --from=build /src/open/copy.sql /copy.sql
COPY --from=build /src/socket/socket /socket
COPY --from=build /src/stat/stat /stat
COPY --from=build /src/stat/rootfs/file /file
COPY --from=build /src/sysconf/sysconf /sysconf

# Libraries
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/
