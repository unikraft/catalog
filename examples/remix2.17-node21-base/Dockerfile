FROM node:21-alpine3.20 AS base

WORKDIR /usr/src

FROM base AS build

COPY package.json /usr/src/package.json
RUN npm install

COPY . /usr/src/
RUN npm run build

FROM base AS runtime

COPY package.json /usr/src/package.json
RUN npm install --omit dev

FROM scratch

COPY --from=build /etc/ssl/certs/ca-certificates.crt /etc/ssl/certs/ca-certificates.crt

# Node binary
COPY --from=build /usr/local/bin/node /usr/bin/node

# System libraries
COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=build /usr/lib/libgcc_s.so.1 /usr/lib/libgcc_s.so.1
COPY --from=build /usr/lib/libstdc++.so.6 /usr/lib/libstdc++.so.6

COPY --from=runtime /usr/src/node_modules /usr/src/node_modules
COPY --from=build /usr/src/build/ /usr/src/build/
COPY --from=build /usr/src/public /usr/src/public
COPY --from=build /usr/src/server.js /usr/src/server.js
COPY --from=build /usr/src/package.json /usr/src/package.json
