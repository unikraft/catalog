FROM --platform=linux/x86_64 perl:5.38.0-bookworm AS build

RUN set -xe ; \
	cpanm HTTP::Daemon

FROM scratch

# Perl binary
COPY --from=build /usr/local/bin/perl /usr/bin/perl

# Perl libraries
COPY --from=build /usr/local/lib/perl5 /usr/local/lib/perl5

# System libraries
COPY --from=build /usr/local/lib/perl5/5.38.0/x86_64-linux-gnu/CORE/libperl.so /usr/local/lib/perl5/5.38.0/x86_64-linux-gnu/CORE/libperl.so
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=build /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/libm.so.6
COPY --from=build /lib/x86_64-linux-gnu/libcrypt.so.1 /lib/x86_64-linux-gnu/libcrypt.so.1
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
COPY --from=build /etc/ld.so.cache /etc/ld.so.cache

# Simple Perl HTTP server
COPY ./server.pl /src/server.pl
