FROM redis:7.2.2-bookworm AS build

FROM gcr.io/distroless/cc-debian12@sha256:e5d81ddde149641e2a9ba55be4545bc125c67de07508b03ba4c22e6eb0ded5aa

# Redis binaries, modules, configuration, log and runtime files
COPY --from=build /usr/local/bin/redis-server /usr/bin/redis-server

# Custom configuration files, including using a single process for Redis
COPY ./redis.conf /etc/redis/redis.conf
