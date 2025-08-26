FROM python:3.10.18-bookworm AS base

WORKDIR /app

COPY requirements.txt /app
RUN pip3 install -r requirements.txt --no-cache-dir

FROM scratch

# Python libraries
COPY --from=base /usr/local/lib/python3.10 /usr/local/lib/python3.10

# Application files
COPY ./server.py /app/server.py
