FROM perl:5.42.0-trixie AS build

RUN set -xe ; \
	cpanm HTTP::Daemon

FROM gcr.io/distroless/cc-debian13@sha256:9b615fff20e1a4fad29c2b30562580b212c7dd5e2225236735cca0070ed11c78

COPY --from=build /usr/local/bin/perl /usr/bin/perl
COPY --from=build /usr/local/lib/perl5 /usr/local/lib/perl5

COPY --from=build /lib/x86_64-linux-gnu/libcrypt.so.1 /lib/x86_64-linux-gnu/libcrypt.so.1

COPY ./server.pl /usr/src/server.pl

