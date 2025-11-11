FROM node:21-alpine AS build

WORKDIR /usr/src/app

COPY package.json package-lock.json ./
RUN npm ci

FROM scratch

COPY --from=build /etc/os-release /etc/os-release
COPY --from=build /usr/src/app/node_modules /usr/src/node_modules
COPY server.js /usr/src/server.js
