FROM python:3.14-trixie AS base

RUN rm -rf /usr/local/lib/python3.14/ensurepip \
           /usr/local/lib/python3.14/site-packages/*

FROM gcr.io/distroless/cc-debian13@sha256:e86cf4f565c8eee2cbb2be073bb107dafb14734b53d5872da20fdf47418a02f4

ENV LD_LIBRARY_PATH=/usr/local/lib

COPY --from=base /usr/local/bin/python3 /usr/local/bin/python3
COPY --from=base /usr/local/lib/python3.14 /usr/local/lib/python3.14
COPY --from=base /usr/local/lib/libpython3.14.so.1.0 /usr/local/lib/libpython3.14.so.1.0

COPY ./server.py /server.py

