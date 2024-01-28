# Simple HTTP Server using 'tokio'

This is a simple HTTP server written in Rust, using the 'tokio' runtime (https://tokio.rs/).
This can be built and run using the ['kraft' command line tool](https://unikraft.org/docs/cli).

First, initialise the bridge network. As 'root' run:

```console
kraft net create -n 172.44.0.1/24 virbr0
```

Then, build using the command:

```console
KRAFTKIT_TARGET=http-tokio cargo +nightly build --target x86_64-unikraft-linux-musl -Z build-std=std,panic_abort
```

To run use the command:

```console
sudo kraft run -W --memory 2G --network bridge:virbr0 -a netdev.ip=172.44.0.2/24:172.44.0.1
```

The server can then be queried:

```console
curl 172.44.0.2:8080
```
