FROM node:22-bookworm-slim AS build

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
  npm run build;

FROM cgr.dev/chainguard/node@sha256:f819ce9bc54ff2a771a6849ec8453aaab9bb697873f3f6b91039ed07a3626748

COPY --from=build /app/dist /usr/src
