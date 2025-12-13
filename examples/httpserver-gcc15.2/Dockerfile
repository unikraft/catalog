FROM gcc:15.2 AS build

WORKDIR /src

COPY ./http_server.c /src/http_server.c

RUN set -xe; \
    gcc \
	-Wall -Wextra \
	-fPIC -pie \
	-o /http_server http_server.c

FROM scratch

COPY --from=build /http_server /http_server
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/
