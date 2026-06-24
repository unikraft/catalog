FROM mcr.microsoft.com/dotnet/sdk:9.0-alpine AS build
RUN apk add --no-cache clang lld musl-dev
WORKDIR /src
COPY Program.cs HelloNativeAot.csproj ./
RUN dotnet publish -c Release -r linux-musl-x64 /p:StaticExecutable=true /p:LinkerFlavor=lld

FROM scratch AS rootfs
COPY --from=build /src/bin/Release/net9.0/linux-musl-x64/publish/HelloNativeAot /bin/hello

# --- CPIO rootfs builder (used by: docker build --target cpio) ---
FROM alpine:3.20 AS cpio
RUN apk add --no-cache cpio findutils
COPY --from=rootfs / /rootfs/
RUN cd /rootfs && find . | cpio -o -H newc > /output.cpio 2>/dev/null
