FROM haskell:9.14.1-slim-bookworm AS build
WORKDIR /opt/app

COPY Main.hs shim.c ./

RUN ghc -O2 -dynamic -fPIC -pie Main.hs shim.c

RUN nm -D Main | grep clock_gettime

RUN mkdir -p /deps && \
  ldd Main | grep "=> /" | awk '{print $3}' | \
  grep -Ev '/(libc|libm|libpthread|libdl|librt|libresolv|libutil|libcrypt|libgcc_s|libstdc\+\+|libssl|libcrypto)[.\-]' | \
  xargs -I '{}' cp --parents '{}' /deps/

FROM gcr.io/distroless/cc-debian12@sha256:e5d81ddde149641e2a9ba55be4545bc125c67de07508b03ba4c22e6eb0ded5aa

COPY --from=build /deps/ /
COPY --from=build /opt/app/Main /app/Main
