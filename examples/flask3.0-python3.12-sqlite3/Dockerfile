FROM python:3.12.11-bookworm AS build

WORKDIR /app

COPY requirements.txt /app/
RUN pip3 install -r requirements.txt --no-cache-dir

COPY . /app/
RUN python3 init_db.py

FROM scratch

# SQLite library
COPY --from=build /usr/lib/x86_64-linux-gnu/libsqlite3.so.0 /usr/lib/x86_64-linux-gnu/libsqlite3.so.0

# Python libraries
COPY --from=build /usr/local/lib/python3.12 /usr/local/lib/python3.12

# Application files
COPY --from=build /app /app
