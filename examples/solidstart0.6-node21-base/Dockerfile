FROM node:21-alpine3.20 AS build

WORKDIR /usr/src

COPY . /usr/src/

RUN set -xe && \
    npm instal -g pnpm && \
    pnpm install && \
    pnpm build

FROM scratch

COPY --from=build /etc/ssl/certs/ca-certificates.crt /etc/ssl/certs/ca-certificates.crt

# Node binary
COPY --from=build /usr/local/bin/node /usr/bin/node

# System libraries
COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=build /usr/lib/libgcc_s.so.1 /usr/lib/libgcc_s.so.1
COPY --from=build /usr/lib/libstdc++.so.6 /usr/lib/libstdc++.so.6

COPY --from=build /usr/src/.output/ /usr/src/
