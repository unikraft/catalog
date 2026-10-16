FROM node:22-alpine AS build

WORKDIR /app

COPY package.json package-lock.json* ./

RUN npm ci --omit=dev 

COPY index.js .

FROM cgr.dev/chainguard/node@sha256:198c07af382e29f21e4f50b39921644599ee5d12bb92397bf7fb624a7a39801b

WORKDIR /app

COPY --from=build /app /app
