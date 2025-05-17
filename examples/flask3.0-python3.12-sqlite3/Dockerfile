FROM python:3.12-bookworm AS build

WORKDIR /app

COPY requirements.txt /app/
RUN pip3 install -r requirements.txt --no-cache-dir

COPY . /app/
RUN python3 init_db.py

FROM scratch

COPY --from=build /usr/lib/x86_64-linux-gnu/libsqlite3.so.0 /usr/lib/x86_64-linux-gnu/libsqlite3.so.0
COPY --from=build /usr/local/lib/python3.12 /usr/local/lib/python3.12
COPY --from=build /app /app
