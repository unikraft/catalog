# Caddy 2.7

This directory contains the definition to run [Caddy](https://github.com/caddyserver/caddy) on Unikraft in binary compatibility mode.

Follow the instructions in the common `../README.md` file to set up and configure the application.

## Quick Run

Use `kraft` to run the image:

```console
kraft run -M 256M -p 2015:2015
```

Once executed, it will open port `2015` and wait for connections, and can be queried.

Query the service using:

```console
curl localhost:2015
```

This doesn't work, however, probably due to some Caddy specifics.

## Scripted Run

Use the scripted runs, detailed in the common `../README.md`.
Once you run the the scripts, query the service:

```console
curl 172.44.0.2:2015
```

This will show a `Hello, World!` message, provided by the Caddy, based on the configuration on `Caddyfile`.
