FROM dart:3.6.1 AS build

COPY helloworld.dart /

# Compile the helloworld.dart file
RUN dart compile exe /helloworld.dart -o /helloworld

FROM scratch

COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2

COPY --from=build /lib/x86_64-linux-gnu/libdl.so.2 \
		  /lib/x86_64-linux-gnu/libpthread.so.0 \
		  /lib/x86_64-linux-gnu/libm.so.6 \
		  /lib/x86_64-linux-gnu/libc.so.6 \
                  /lib/x86_64-linux-gnu/

COPY --from=build /helloworld /helloworld

