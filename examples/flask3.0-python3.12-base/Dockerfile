FROM python:3.12 AS base

RUN /usr/sbin/ldconfig /usr/local/lib

WORKDIR /app

COPY requirements.txt /app

RUN pip3 install -r requirements.txt --no-cache-dir

FROM scratch

# System libraries
COPY --from=base /usr/local/lib/python3.12 /usr/local/lib/python3.12
COPY --from=base /usr/local/bin/../lib/libpython3.12.so.1.0 /usr/local/bin/../lib/libpython3.12.so.1.0
COPY --from=base /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=base /lib/x86_64-linux-gnu/libpthread.so.0 /lib/x86_64-linux-gnu/libpthread.so.0
COPY --from=base /lib/x86_64-linux-gnu/libdl.so.2 /lib/x86_64-linux-gnu/libdl.so.2
COPY --from=base /lib/x86_64-linux-gnu/libutil.so.1 /lib/x86_64-linux-gnu/libutil.so.1
COPY --from=base /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/libm.so.6
COPY --from=base /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
COPY --from=base /lib/x86_64-linux-gnu/libz.so.1 /lib/x86_64-linux-gnu/libz.so.1
COPY --from=base /usr/lib/x86_64-linux-gnu/gconv/gconv-modules.cache /usr/lib/x86_64-linux-gnu/gconv/gconv-modules.cache
COPY --from=base /lib/x86_64-linux-gnu/libtinfo.so.6 /lib/x86_64-linux-gnu/libtinfo.so.6
COPY --from=base /lib/terminfo/x/xterm /lib/terminfo/x/xterm
COPY --from=base /etc/inputrc /etc/inputrc
COPY --from=base /etc/group /etc/group

# Python libraries
COPY --from=base /usr/local/lib /usr/local/lib
COPY --from=base /usr/lib/x86_64-linux-gnu/libz.so.1 /usr/lib/x86_64-linux-gnu/libz.so.1
COPY --from=base /etc/ld.so.cache /etc/ld.so.cache

# Python executable
COPY --from=base /usr/local/bin/python3 /usr/local/bin/python3

# Python files
COPY ./server.py /app/server.py

