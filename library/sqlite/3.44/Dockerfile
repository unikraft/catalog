FROM keinos/sqlite3 as build
FROM scratch

COPY --from=build /usr/bin/sqlite3 /usr/bin/sqlite3

COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=build /usr/lib/libz.so.1 /usr/lib/libz.so.1
COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1

COPY ./build.sql build.sql
COPY ./query.sql query.sql
COPY ./init.sql init.sql
