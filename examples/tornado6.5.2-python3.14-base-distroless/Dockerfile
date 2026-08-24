FROM python:3.14 AS base

WORKDIR /app

COPY requirements.txt /app

RUN pip3 install --upgrade pip setuptools \
  && pip3 install --upgrade -r requirements.txt --no-cache-dir \
  && rm -rf /usr/local/lib/python3.14/ensurepip

FROM gcr.io/distroless/cc-debian13@sha256:e86cf4f565c8eee2cbb2be073bb107dafb14734b53d5872da20fdf47418a02f4

COPY --from=base /usr/local/lib/python3.14 /usr/local/lib/python3.14
COPY --from=base /usr/local/bin/../lib/libpython3.14.so.1.0 /usr/local/bin/../lib/libpython3.14.so.1.0
COPY --from=base /usr/local/bin/python3 /usr/local/bin/python3

COPY ./server.py /app/server.py
