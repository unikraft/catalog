FROM node:21-alpine AS build

WORKDIR /usr/src

COPY . /usr/src/

RUN npm install

FROM cgr.dev/chainguard/node@sha256:105c8e7e503ea8f45553b9cc5aa0d24e80499bcc7c860dff54449e7c01d9be79

# Express.js
COPY --from=build /usr/src/node_modules /usr/src/node_modules
COPY --from=build /usr/src/app/index.js /usr/src/server.js
