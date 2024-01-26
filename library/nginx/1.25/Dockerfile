FROM nginx:1.25.3-bookworm AS build

# These are normally syminks to /dev/stdout and /dev/stderr, which don't
# (currently) work with Unikraft. We remove them, such that Nginx will create
# them by hand.
RUN rm /var/log/nginx/error.log
RUN rm /var/log/nginx/access.log

FROM scratch

# Nginx binaries, modules, configuration, log and runtime files
COPY --from=build /usr/sbin/nginx /usr/bin/nginx
COPY --from=build /usr/lib/nginx /usr/lib/nginx
COPY --from=build /etc/nginx /etc/nginx
COPY --from=build /etc/passwd /etc/passwd
COPY --from=build /etc/group /etc/group
COPY --from=build /var/log/nginx /var/log/nginx
COPY --from=build /var/cache/nginx /var/cache/nginx
COPY --from=build /var/run /var/run

# Libraries
COPY --from=build /lib/x86_64-linux-gnu/libcrypt.so.1 /lib/x86_64-linux-gnu/libcrypt.so.1
COPY --from=build /lib/x86_64-linux-gnu/libpcre2-8.so.0 /lib/x86_64-linux-gnu/libpcre2-8.so.0
COPY --from=build /lib/x86_64-linux-gnu/libssl.so.3 /lib/x86_64-linux-gnu/libssl.so.3
COPY --from=build /lib/x86_64-linux-gnu/libcrypto.so.3 /lib/x86_64-linux-gnu/libcrypto.so.3
COPY --from=build /lib/x86_64-linux-gnu/libz.so.1 /lib/x86_64-linux-gnu/libz.so.1
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
COPY --from=build /etc/ld.so.cache /etc/ld.so.cache

# Custom configuration files, including using a single process for Nginx
COPY ./conf/nginx.conf /etc/nginx/nginx.conf

# Web root
COPY ./wwwroot /wwwroot
