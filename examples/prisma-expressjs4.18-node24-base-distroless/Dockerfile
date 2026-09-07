FROM node:24-bookworm-slim AS build

WORKDIR /app

RUN apt-get update && apt-get install -y openssl ca-certificates tzdata

# Install dependencies
COPY ./package.json /app/
RUN npm install

# Copy source code and config
COPY ./webpack.config.js /app/
COPY ./src /app/src
COPY ./prisma /app/prisma

# Generate Prisma client
RUN set -xe; \
    npx prisma generate; \
    npx prisma migrate deploy; \
    npx prisma db seed; \
    npm run build;

FROM cgr.dev/chainguard/node@sha256:44e06504d7a99cfbf10a6ce9777c21fed05fa0f8ca29c24615b68683bf0184a1

COPY --from=build /app/dist /usr/src

