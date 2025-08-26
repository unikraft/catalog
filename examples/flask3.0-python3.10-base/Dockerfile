FROM python:3.10.18-bookworm AS base

WORKDIR /app

COPY requirements.txt /app
RUN pip3 install -r requirements.txt --no-cache-dir

RUN /usr/sbin/ldconfig /usr/local/lib

FROM scratch

# Python executable
COPY --from=base /usr/local/bin/python3 /usr/local/bin/python3

# System libraries
COPY --from=base \
                 /lib/x86_64-linux-gnu/libc.so.6 \
                 /lib/x86_64-linux-gnu/libdl.so.2 \
                 /lib/x86_64-linux-gnu/libm.so.6 \
                 /lib/x86_64-linux-gnu/libpthread.so.0 \
                 /lib/x86_64-linux-gnu/libutil.so.1 \
                 /lib/x86_64-linux-gnu/libz.so.1 \
                 /lib/x86_64-linux-gnu/

# Python libraries
COPY --from=base /usr/local/lib /usr/local/lib

# Dynamic linker / loader
COPY --from=base /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2

# Dynamic linker cache
COPY --from=base /etc/ld.so.cache /etc/ld.so.cache

# Application files
COPY ./server.py /app/server.py
