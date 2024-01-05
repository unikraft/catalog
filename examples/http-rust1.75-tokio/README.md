# Simple HTTP `Tokio` Server

This is a simple HTTP server written in [Rust](https://www.rust-lang.org/) using the [`Tokio` runtime](https://tokio.rs/).
To run this example, first [install the `kraft` command-line tool](https://unikraft.org/docs/cli).

Then, clone this repository and `cd` into this directory.
Make sure you have the [`BuildKit`](https://docs.docker.com/build/buildkit/) container started:

```console
docker run -d --name buildkitd --privileged moby/buildkit:latest
export KRAFTKIT_BUILDKIT_HOST=docker-container://buildkitd
```

Then run:

```console
kraft run --plat qemu --arch x86_64 -p 8080:8080 -M 128M .
```

Query the server using:

```console
curl localhost:8080
```

You will get a `Hello, World!` message.

## Learn More

- [Unikraft Documentation](https://unikraft.org/docs/cli)
- [How to build `Dockerfile` root filesystems with `BuildKit`](https://unikraft.org/docs/getting-started/integrations/buildkit)
