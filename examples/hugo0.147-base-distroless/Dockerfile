FROM golang:1.21.3-bookworm AS build

ARG HUGO_VERSION=v0.122.0

WORKDIR /src

RUN set -xe; \
  CGO_ENABLED=1 \
  go install \
  -buildmode=pie \
  -tags extended \
  github.com/gohugoio/hugo@${HUGO_VERSION} \
  ;

WORKDIR /site

RUN set -xe; \
  /go/bin/hugo new site .; \
  git clone --depth 1 https://github.com/budparr/gohugo-theme-ananke.git themes/ananke; \
  echo 'theme = "ananke"' >> hugo.toml \
  ;

FROM gcr.io/distroless/cc-debian12@sha256:e5d81ddde149641e2a9ba55be4545bc125c67de07508b03ba4c22e6eb0ded5aa

COPY --from=build /go/bin/hugo /usr/bin/hugo

COPY site /site
