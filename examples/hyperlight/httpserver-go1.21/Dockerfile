FROM golang:1.21.3-bookworm AS build

WORKDIR /src

COPY ./server.go /src/server.go

RUN set -xe; \
    CGO_ENABLED=0 \
    GOARCH=amd64 \
    go build \
      -buildmode=pie \
      -ldflags="-linkmode=internal" \
      -o /server server.go \
    ;

# Strip PT_INTERP from the static PIE binary: Go's internal linker adds
# /lib64/ld-linux-x86-64.so.2 as interpreter for PIE on Linux, but the
# binary is fully self-contained and does not need a dynamic linker.
# Unikraft's elfloader fails when the interpreter is listed but absent.
# Patch the program header: change PT_INTERP (type=3) -> PT_NULL (type=0).
COPY patch_interp.py /patch_interp.py
RUN python3 /patch_interp.py /server

FROM scratch

COPY --from=build /server /bin/server