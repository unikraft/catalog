FROM gcc:15.2 AS build

WORKDIR /src

COPY ./helloworld.c /src/helloworld.c

RUN set -xe; \
    gcc \
	-Wall -Wextra \
	-fPIC -pie \
	-o /helloworld helloworld.c

FROM scratch

COPY --from=build /helloworld /helloworld
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/
