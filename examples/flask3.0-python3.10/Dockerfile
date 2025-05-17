FROM python:3.10.11 AS base

WORKDIR /app

COPY requirements.txt /app

RUN pip3 install -r requirements.txt --no-cache-dir

FROM scratch

COPY --from=base /usr/local/lib/python3.10 /usr/local/lib/python3.10
COPY ./server.py /app/server.py
