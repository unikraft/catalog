FROM bitnami/grafana:10.3.3


# Copy necessary libraries
COPY --from=bitnami/grafana:10.3.3 /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=bitnami/grafana:10.3.3 /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
COPY --from=bitnami/grafana:10.3.3 /etc/ld.so.cache /etc/ld.so.cache

CMD ["/opt/bitnami/grafana/bin/grafana-server"]
