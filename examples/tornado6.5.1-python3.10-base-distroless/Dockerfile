FROM python:3.10.11 AS base

WORKDIR /app

COPY requirements.txt /app

RUN pip3 install -r requirements.txt --no-cache-dir

FROM gcr.io/distroless/cc-debian13

# Python runtime
COPY --from=base /usr/local/lib/python3.10 /usr/local/lib/python3.10
COPY --from=base /usr/local/lib/libpython3.10.so.1.0 /usr/local/lib/libpython3.10.so.1.0
COPY --from=base /usr/local/bin/python3 /usr/local/bin/python3

# OpenSSL required by Python ssl module
COPY --from=base /usr/lib/x86_64-linux-gnu/libssl.so.1.1 /usr/lib/x86_64-linux-gnu/libssl.so.1.1
COPY --from=base /usr/lib/x86_64-linux-gnu/libcrypto.so.1.1 /usr/lib/x86_64-linux-gnu/libcrypto.so.1.1

# Application
COPY ./server.py /app/server.py

CMD ["/usr/local/bin/python3", "/app/server.py"]