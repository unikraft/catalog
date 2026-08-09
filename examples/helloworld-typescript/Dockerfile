
FROM node:21-alpine AS build

WORKDIR /usr/src


COPY package.json package-lock.json ./

RUN npm install


COPY . ./


RUN npm run build


FROM scratch


COPY --from=build /etc/os-release /etc/os-release


COPY --from=build /usr/src/node_modules /usr/src/node_modules
COPY --from=build /usr/src/dist /usr/src/dist
COPY --from=build /usr/src/package.json /usr/src/

