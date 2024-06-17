FROM debian:bookworm AS build

# Necessary tools for instalation
RUN apt-get update && apt-get install curl xz-utils -y

# Install Zig-0.11.0
RUN curl https://ziglang.org/download/0.11.0/zig-linux-x86_64-0.11.0.tar.xz > zig-linux-x86_64-0.11.0.tar.xz && \
    tar -xf zig-linux-x86_64-0.11.0.tar.xz && \
    mv zig-linux-x86_64-0.11.0 /usr/local/bin/zig && \
    chmod +x /usr/local/bin/zig

ENV PATH="/usr/local/bin/zig:${PATH}"

COPY helloworld.zig /

# Compile the helloworld.zig file
RUN zig build-exe helloworld.zig -fPIE -static

FROM scratch

COPY --from=build /helloworld /helloworld
