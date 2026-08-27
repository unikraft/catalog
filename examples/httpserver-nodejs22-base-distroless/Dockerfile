FROM node:22-alpine AS node

FROM scratch

# Dynamic linker
COPY --from=node /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1

# Node binary
COPY --from=node /usr/local/bin/node /usr/bin/node

# Required libraries
COPY --from=node /usr/lib /usr/lib

# Node HTTP server
COPY ./src /usr/src

CMD ["/usr/bin/node", "/usr/src/server.js"]