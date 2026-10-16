FROM node:18-bookworm-slim AS build

WORKDIR /app

RUN apt-get update && apt-get install -y openssl ca-certificates tzdata

COPY ./package.json /app/

RUN npm install

COPY ./webpack.config.js /app/
COPY ./src /app/src
COPY ./prisma /app/prisma

RUN set -xe; \
  npx prisma generate; \
  npx prisma migrate deploy; \
  npx prisma db seed; \
  npm run build \
  ;

FROM cgr.dev/chainguard/node@sha256:105c8e7e503ea8f45553b9cc5aa0d24e80499bcc7c860dff54449e7c01d9be79

ENV PRISMA_CLIENT_ENGINE_TYPE=library
ENV PRISMA_CLI_QUERY_ENGINE_TYPE=library

# rest-express + Prisma
COPY --from=build /app/dist /usr/src
COPY --from=build /app/node_modules/.prisma /usr/src/node_modules/.prisma
