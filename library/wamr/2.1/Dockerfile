FROM ghcr.io/webassembly/wasi-sdk AS build

WORKDIR /app
COPY ./helloworld.c .
RUN /opt/wasi-sdk/bin/clang -O3 -o helloworld.wasm helloworld.c

FROM ubuntu:22.04 AS wamrc-build

ARG WAMR_VERSION=2.1.2

RUN set -xe; \
    apt -yqq update; \
    apt -yqq install wget \
    ;

WORKDIR /usr/local/bin
RUN set -xe; \
    wget https://github.com/bytecodealliance/wasm-micro-runtime/releases/download/WAMR-${WAMR_VERSION}/wamrc-${WAMR_VERSION}-x86_64-ubuntu-22.04.tar.gz; \
    tar xf wamrc-${WAMR_VERSION}-x86_64-ubuntu-22.04.tar.gz \
    ;

WORKDIR /app
COPY --from=build /app/helloworld.wasm .
RUN /usr/local/bin/wamrc -o helloworld.aot helloworld.wasm

FROM ubuntu:22.04 AS iwasm-down

ARG WAMR_VERSION=2.1.2

RUN set -xe; \
    apt -yqq update; \
    apt -yqq install wget \
    ;

WORKDIR /usr/local/bin
RUN set -xe; \
    wget https://github.com/bytecodealliance/wasm-micro-runtime/releases/download/WAMR-${WAMR_VERSION}/iwasm-${WAMR_VERSION}-x86_64-ubuntu-22.04.tar.gz; \
    tar xf iwasm-${WAMR_VERSION}-x86_64-ubuntu-22.04.tar.gz \
    ;

FROM scratch

# Copy iwasm binary.
COPY --from=iwasm-down /usr/local/bin/iwasm /usr/bin/iwasm

# Copy iwasm libraries.
COPY --from=iwasm-down /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/libm.so.6
COPY --from=iwasm-down /lib/x86_64-linux-gnu/libz.so.1 /lib/x86_64-linux-gnu/libz.so.1
COPY --from=iwasm-down /lib/x86_64-linux-gnu/libzstd.so.1 /lib/x86_64-linux-gnu/libzstd.so.1
COPY --from=iwasm-down /lib/x86_64-linux-gnu/libstdc++.so.6 /lib/x86_64-linux-gnu/libstdc++.so.6
COPY --from=iwasm-down /lib/x86_64-linux-gnu/libgcc_s.so.1 /lib/x86_64-linux-gnu/libgcc_s.so.1
COPY --from=iwasm-down /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=iwasm-down /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2

# COPY AoT file.
COPY --from=wamrc-build /app/helloworld.aot /app/helloworld.aot
