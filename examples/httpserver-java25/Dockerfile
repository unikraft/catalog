FROM openjdk:25-rc-oraclelinux9 AS build

ENV JAVA_HOME=/usr/java/openjdk-25

RUN ldconfig $JAVA_HOME/lib/server/

WORKDIR /src

COPY ./SimpleHttpServer.java /src/SimpleHttpServer.java

RUN javac SimpleHttpServer.java

FROM alpine:3 AS sys

FROM scratch

COPY --from=build /usr/lib64/libc.so.6 /usr/lib64/
COPY --from=build /usr/lib64/libstdc++.so.6 /usr/lib64/
COPY --from=build /usr/lib64/libm.so.6 /usr/lib64/
COPY --from=build /usr/lib64/libz.so.1 /usr/lib64/
COPY --from=build /usr/lib64/libgcc_s.so.1 /usr/lib64/
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/
COPY --from=build /etc/ld.so.cache /etc/ld.so.cache

COPY --from=build $JAVA_HOME/ /usr/lib/jvm/java-25-runtime/

COPY --from=build /src/SimpleHttpServer.class /usr/src/SimpleHttpServer.class
