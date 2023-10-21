FROM python:3.10.11 AS base

FROM scratch

COPY --from=base /usr/lib/python3/ /usr/lib/python3/
COPY --from=base /usr/lib/python3.9/ /lib/python3.10/

COPY ./server.py /server.py
