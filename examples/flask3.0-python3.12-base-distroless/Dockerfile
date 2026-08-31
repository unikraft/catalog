FROM python:3.12.11-bookworm AS base

WORKDIR /app

COPY requirements.txt /app
RUN pip3 install -r requirements.txt --no-cache-dir

FROM gcr.io/distroless/cc-debian12@sha256:e5d81ddde149641e2a9ba55be4545bc125c67de07508b03ba4c22e6eb0ded5aa

COPY --from=base /usr/local/bin/python3 /usr/local/bin/python3
COPY --from=base /usr/local/lib /usr/local/lib
COPY --from=base /lib/x86_64-linux-gnu/libz.so.1 /lib/x86_64-linux-gnu/libz.so.1
COPY ./server.py /app/server.py
