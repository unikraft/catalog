FROM python:3.10.18-bookworm AS base

WORKDIR /app

COPY requirements.txt /app/requirements.txt

RUN pip3 install --no-cache-dir -r requirements.txt

RUN /usr/sbin/ldconfig /usr/local/lib

FROM scratch

# Python executable
COPY --from=base /usr/local/bin/python3 /usr/local/bin/python3

# Python libraries
COPY --from=base /usr/local/lib /usr/local/lib

# System libraries
COPY --from=base /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=base /lib/x86_64-linux-gnu/libdl.so.2 /lib/x86_64-linux-gnu/libdl.so.2
COPY --from=base /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/libm.so.6
COPY --from=base /lib/x86_64-linux-gnu/libpthread.so.0 /lib/x86_64-linux-gnu/libpthread.so.0
COPY --from=base /lib/x86_64-linux-gnu/libutil.so.1 /lib/x86_64-linux-gnu/libutil.so.1
COPY --from=base /lib/x86_64-linux-gnu/libz.so.1 /lib/x86_64-linux-gnu/libz.so.1

# Dynamic linker / loader
COPY --from=base /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2

# Dynamic linker cache
COPY --from=base /etc/ld.so.cache /etc/ld.so.cache

# Application
COPY server.py /app/server.py

CMD ["/usr/local/bin/python3", "/app/server.py"]