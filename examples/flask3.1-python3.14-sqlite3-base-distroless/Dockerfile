FROM python:3.14.0-trixie AS base

WORKDIR /app

COPY requirements.txt /app
RUN pip3 install -r requirements.txt --no-cache-dir

COPY init_db.py schema.sql /app/
RUN python3 init_db.py

FROM gcr.io/distroless/cc-debian13@sha256:e86cf4f565c8eee2cbb2be073bb107dafb14734b53d5872da20fdf47418a02f4

ENV LD_LIBRARY_PATH=/usr/local/lib

COPY --from=base /usr/local/bin/python3 /usr/local/bin/python3
COPY --from=base /usr/local/lib/python3.14 /usr/local/lib/python3.14
COPY --from=base /usr/local/lib/libpython3.14.so.1.0 /usr/local/lib/libpython3.14.so.1.0
COPY --from=base /lib/x86_64-linux-gnu/libsqlite3.so.0 /lib/x86_64-linux-gnu/libsqlite3.so.0

COPY --from=base /app /app

COPY ./server.py /app/server.py
COPY ./templates /app/templates
COPY ./static /app/static

WORKDIR /app

