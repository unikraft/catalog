FROM ocaml/opam:debian as build
RUN sudo apt update && \
    sudo apt install -y build-essential libgmp-dev pkg-config && \
    opam update && \
    opam install dune cohttp-lwt-unix --yes
WORKDIR /app
COPY dune dune-project server.ml ./
RUN eval $(opam env) && dune build server.exe

FROM scratch
WORKDIR /app
COPY --from=build /app/_build/default/server.exe /app/server.exe
COPY --from=build /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/
COPY --from=build /etc/ld.so.cache /etc/
EXPOSE 8080
ENTRYPOINT ["/app/server.exe"]