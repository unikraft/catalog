FROM mariadb:11.2.2-jammy as build

ENV MARIADB_ROOT_PASSWORD="unikraft"

RUN /usr/bin/sed -i '/^[ \t]\+exec "\$@"/d' /usr/local/bin/docker-entrypoint.sh
RUN /usr/local/bin/docker-entrypoint.sh mariadbd
RUN /usr/bin/sed -i 's/^#\(user[ \t]\+\).*$/\1= root/g' /etc/mysql/mariadb.conf.d/50-server.cnf
RUN /usr/bin/sed -i 's/^#\(bind-address[ \t]\+\).*$/\1= 0.0.0.0/g' /etc/mysql/mariadb.conf.d/50-server.cnf

RUN mkdir -p /home/run/mysqld

FROM alpine:3 AS sys

RUN set -xe; \
    mkdir -p /target/etc; \
    mkdir -p /blank; \
    apk --no-cache add \
      ca-certificates \
      tzdata \
    ; \
    update-ca-certificates; \
    ln -sf ../usr/share/zoneinfo/Etc/UTC /target/etc/localtime; \
    echo "Etc/UTC" > /target/etc/timezone;

FROM scratch

COPY --from=sys /target/etc /etc
COPY --from=sys /usr/share/zoneinfo/Etc/UTC /usr/share/zoneinfo/Etc/UTC
COPY --from=sys /etc/ssl/certs/ca-certificates.crt /etc/ssl/certs/ca-certificates.crt
COPY --from=sys /blank /tmp

COPY --from=build /usr/sbin/mariadbd /usr/sbin/mariadbd
COPY --from=build /home/run/mysqld /run/mysqld

COPY --from=build /var/lib /var/lib
COPY --from=build /etc/mysql /etc/mysql
COPY --from=build /usr/lib/mysql /usr/lib/mysql

COPY --from=build /lib/x86_64-linux-gnu/libpcre2-8.so.0 /lib/x86_64-linux-gnu/libpcre2-8.so.0
COPY --from=build /lib/x86_64-linux-gnu/libcrypt.so.1 /lib/x86_64-linux-gnu/libcrypt.so.1
COPY --from=build /lib/x86_64-linux-gnu/liburing.so.2 /lib/x86_64-linux-gnu/liburing.so.2
COPY --from=build /lib/x86_64-linux-gnu/libpmem.so.1 /lib/x86_64-linux-gnu/libpmem.so.1
COPY --from=build /lib/x86_64-linux-gnu/libsystemd.so.0 /lib/x86_64-linux-gnu/libsystemd.so.0
COPY --from=build /lib/x86_64-linux-gnu/libz.so.1 /lib/x86_64-linux-gnu/libz.so.1
COPY --from=build /lib/x86_64-linux-gnu/libssl.so.3 /lib/x86_64-linux-gnu/libssl.so.3
COPY --from=build /lib/x86_64-linux-gnu/libcrypto.so.3 /lib/x86_64-linux-gnu/libcrypto.so.3
COPY --from=build /lib/x86_64-linux-gnu/libstdc++.so.6 /lib/x86_64-linux-gnu/libstdc++.so.6
COPY --from=build /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/libm.so.6
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
COPY --from=build /lib/x86_64-linux-gnu/libndctl.so.6 /lib/x86_64-linux-gnu/libndctl.so.6
COPY --from=build /lib/x86_64-linux-gnu/libdaxctl.so.1 /lib/x86_64-linux-gnu/libdaxctl.so.1
COPY --from=build /lib/x86_64-linux-gnu/liblzma.so.5 /lib/x86_64-linux-gnu/liblzma.so.5
COPY --from=build /lib/x86_64-linux-gnu/libzstd.so.1 /lib/x86_64-linux-gnu/libzstd.so.1
COPY --from=build /lib/x86_64-linux-gnu/liblz4.so.1 /lib/x86_64-linux-gnu/liblz4.so.1
COPY --from=build /lib/x86_64-linux-gnu/libcap.so.2 /lib/x86_64-linux-gnu/libcap.so.2
COPY --from=build /lib/x86_64-linux-gnu/libgcrypt.so.20 /lib/x86_64-linux-gnu/libgcrypt.so.20
COPY --from=build /lib/x86_64-linux-gnu/libgcc_s.so.1 /lib/x86_64-linux-gnu/libgcc_s.so.1
COPY --from=build /lib/x86_64-linux-gnu/libudev.so.1 /lib/x86_64-linux-gnu/libudev.so.1
COPY --from=build /lib/x86_64-linux-gnu/libuuid.so.1 /lib/x86_64-linux-gnu/libuuid.so.1
COPY --from=build /lib/x86_64-linux-gnu/libkmod.so.2 /lib/x86_64-linux-gnu/libkmod.so.2
COPY --from=build /lib/x86_64-linux-gnu/libgpg-error.so.0 /lib/x86_64-linux-gnu/libgpg-error.so.0
