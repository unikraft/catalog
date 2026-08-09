FROM alpine:3.19 AS builder

RUN apk add --no-cache gcc musl-dev make autoconf automake git

RUN git clone --depth 1 --branch 1.11.2 https://github.com/tinyproxy/tinyproxy.git /app
WORKDIR /app

RUN ./autogen.sh
RUN ./configure CFLAGS="-fPIE -Os" LDFLAGS="-static-pie" --disable-regexcheck
RUN make -j$(nproc)

RUN echo "Port 8888" > /tinyproxy.conf && \
    echo "Listen 0.0.0.0" >> /tinyproxy.conf && \
    echo "Timeout 600" >> /tinyproxy.conf && \
    echo "Allow 0.0.0.0/0" >> /tinyproxy.conf && \
    echo "LogFile \"/dev/stdout\"" >> /tinyproxy.conf && \
    echo "LogLevel Info" >> /tinyproxy.conf && \
    echo "MaxClients 100" >> /tinyproxy.conf && \
    echo "PidFile \"/tmp/tinyproxy.pid\"" >> /tinyproxy.conf

RUN mkdir -p /tmp /var/run /etc/ssl/certs
RUN apk add --no-cache ca-certificates

FROM scratch
COPY --from=builder /app/src/tinyproxy /tinyproxy
COPY --from=builder /tinyproxy.conf /tinyproxy.conf
COPY --from=builder /tmp /tmp
COPY --from=builder /var/run /var/run
COPY --from=builder /etc/ssl/certs/ca-certificates.crt /etc/ssl/certs/