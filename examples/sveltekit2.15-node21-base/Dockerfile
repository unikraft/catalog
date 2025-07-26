FROM node:21-alpine3.20 AS deps

WORKDIR /app

COPY package.json /app

RUN npm install

FROM deps AS build

COPY . /app

RUN npm run build; \
    npm prune --omit=dev

RUN <<EOF cat >> /app/build/package.json
{"type": "module"}
EOF

FROM scratch AS prod

COPY --from=build /etc/ssl/certs/ca-certificates.crt /etc/ssl/certs/ca-certificates.crt

# Node binary
COPY --from=build /usr/local/bin/node /usr/bin/node

# System libraries
COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=build /usr/lib/libgcc_s.so.1 /usr/lib/libgcc_s.so.1
COPY --from=build /usr/lib/libstdc++.so.6 /usr/lib/libstdc++.so.6

COPY --from=build /app/build /app/build
COPY --from=build /app/node_modules /app/node_modules
