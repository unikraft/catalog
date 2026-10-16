FROM node:22-alpine AS build

WORKDIR /app

COPY package.json package-lock.json ./

RUN npm ci --omit=dev

COPY index.js .

FROM cgr.dev/chainguard/node@sha256:22568f2da241f7bbe75f381a8d110e19376bd380eb41c62695c4c0f80e4c8396

WORKDIR /app

COPY --from=build /app /app
