FROM nginx:1.31.0-alpine AS build

# error.log and access.log are symlinks to /dev/stdout and /dev/stderr, which
# don't (currently) work with Unikraft. We remove them, such that Nginx will
# create them by hand.
RUN rm /var/log/nginx/error.log
RUN rm /var/log/nginx/access.log

FROM scratch

# Nginx binary, modules, configuration, log and runtime files
COPY --from=build /usr/sbin/nginx /usr/bin/nginx
COPY --from=build /usr/lib/nginx /usr/lib/nginx
COPY --from=build /etc/nginx /etc/nginx
COPY --from=build /etc/passwd /etc/passwd
COPY --from=build /etc/group /etc/group
COPY --from=build /var/log/nginx /var/log/nginx
COPY --from=build /var/cache/nginx /var/cache/nginx
COPY --from=build /run /run

# musl C library / dynamic loader  and nginx's shared library dependencies
COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=build /lib/libc.musl-x86_64.so.1 /lib/libc.musl-x86_64.so.1
COPY --from=build /usr/lib/libpcre2-8.so.0 /usr/lib/libpcre2-8.so.0
COPY --from=build /usr/lib/libssl.so.3 /usr/lib/libssl.so.3
COPY --from=build /usr/lib/libcrypto.so.3 /usr/lib/libcrypto.so.3
COPY --from=build /usr/lib/libz.so.1 /usr/lib/libz.so.1

# Custom configuration files, including using a single process for Nginx
COPY ./conf/nginx.conf /etc/nginx/nginx.conf

# Web root
COPY ./wwwroot /wwwroot
