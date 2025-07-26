FROM node:21-alpine3.20 AS build

WORKDIR /usr/src

COPY . /usr/src/

RUN set -xe; \
    npm install; \
    npm run build

FROM scratch

# Node binary
COPY --from=build /usr/local/bin/node /usr/bin/node

# System libraries
COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=build /usr/lib/libgcc_s.so.1 /usr/lib/libgcc_s.so.1
COPY --from=build /usr/lib/libstdc++.so.6 /usr/lib/libstdc++.so.6

COPY --from=build /usr/src/.next/standalone /usr/src/
COPY --from=build /usr/src/.next/static /usr/src/.next/static
COPY ./public /usr/src/public
