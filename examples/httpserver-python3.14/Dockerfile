FROM python:3.14 AS base

FROM scratch

COPY --from=base /usr/local/lib/python3.14 /usr/local/lib/python3.14

COPY ./server.py /server.py
