FROM python:3.10.11-slim-bullseye AS python

FROM gcr.io/distroless/base-debian12

# Python executable and standard library
COPY --from=python /usr/local/bin/python3 /usr/local/bin/python3
COPY --from=python /usr/local/lib/python3.10 /usr/local/lib/python3.10

# Python shared library
COPY --from=python /usr/local/lib/libpython3.10.so.1.0 /usr/local/lib/libpython3.10.so.1.0

# System libraries
COPY --from=python /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=python /lib/x86_64-linux-gnu/libpthread.so.0 /lib/x86_64-linux-gnu/libpthread.so.0
COPY --from=python /lib/x86_64-linux-gnu/libdl.so.2 /lib/x86_64-linux-gnu/libdl.so.2
COPY --from=python /lib/x86_64-linux-gnu/libutil.so.1 /lib/x86_64-linux-gnu/libutil.so.1
COPY --from=python /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/libm.so.6
COPY --from=python /lib/x86_64-linux-gnu/libz.so.1 /lib/x86_64-linux-gnu/libz.so.1

# Dynamic linker
COPY --from=python /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2

# Application
COPY ./server.py /server.py

CMD ["/usr/local/bin/python3", "/server.py"]