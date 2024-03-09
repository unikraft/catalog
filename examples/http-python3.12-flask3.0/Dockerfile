FROM python:3.12-bookworm AS base

WORKDIR /app

COPY requirements.txt /app

RUN pip3 install -r requirements.txt --no-cache-dir

FROM scratch

COPY --from=base /usr/local/lib/python3.12 /usr/local/lib/python3.12
COPY ./server.py /app/server.py
