FROM eclipse-mosquitto:2.0.21 AS build
FROM scratch

COPY --from=build /usr/sbin/mosquitto /usr/sbin/mosquitto

COPY --from=build /lib/ld-musl-x86_64.so.1 /lib/ld-musl-x86_64.so.1
COPY --from=build /usr/lib/libssl.so.3 /usr/lib/libssl.so.3
COPY --from=build /usr/lib/libcrypto.so.3 /usr/lib/libcrypto.so.3

COPY ./mosquitto.conf mosquitto.conf
