FROM node:24-bookworm-slim AS build

WORKDIR /usr/src

COPY . /usr/src/

RUN npm install

FROM cgr.dev/chainguard/node@sha256:44e06504d7a99cfbf10a6ce9777c21fed05fa0f8ca29c24615b68683bf0184a1

COPY --from=build /usr/src/node_modules /usr/src/node_modules
COPY --from=build /usr/src/app/index.js /usr/src/server.js

