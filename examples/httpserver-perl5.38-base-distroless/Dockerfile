FROM perl:5.38.0-bookworm AS build

RUN set -xe ; \
  cpanm HTTP::Daemon

FROM gcr.io/distroless/cc-debian12@sha256:e5d81ddde149641e2a9ba55be4545bc125c67de07508b03ba4c22e6eb0ded5aa

COPY --from=build /usr/local/bin/perl /usr/bin/perl
COPY --from=build /usr/local/lib/perl5 /usr/local/lib/perl5
COPY --from=build /usr/local/lib/perl5/5.38.0/x86_64-linux-gnu/CORE/libperl.so /usr/local/lib/perl5/5.38.0/x86_64-linux-gnu/CORE/libperl.so
COPY --from=build /lib/x86_64-linux-gnu/libcrypt.so.1 /lib/x86_64-linux-gnu/libcrypt.so.1

COPY ./server.pl /usr/src/server.pl
