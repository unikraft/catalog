FROM keinos/sqlite3:3.44.2 AS build
FROM scratch

COPY --from=build /usr/bin/sqlite3 /usr/bin/sqlite3

COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=build /lib/libz.so.1 /lib/libz.so.1

COPY ./build.sql build.sql
COPY ./query.sql query.sql
COPY ./init.sql init.sql
