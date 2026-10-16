FROM mcr.microsoft.com/dotnet/sdk:9.0-bookworm-slim AS build

RUN apt-get update && apt-get install -y clang zlib1g-dev

WORKDIR /source

COPY app.csproj .
COPY Program.cs .

RUN set -xe; \
    dotnet publish \
    -c Release \
    -r linux-x64 \
    -o /publish

FROM gcr.io/distroless/cc-debian13@sha256:e86cf4f565c8eee2cbb2be073bb107dafb14734b53d5872da20fdf47418a02f4

COPY --from=build /publish/app /app

