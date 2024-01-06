# Simple HTTP `Tokio` Server

This is a simple HTTP server written in [Rust](https://www.rust-lang.org/) using the [`Tokio` runtime](https://tokio.rs/).
To run this example, first [install the `kraft` command-line tool](https://unikraft.org/docs/cli).

Then, clone this repository and `cd` into this directory.
Make sure you have the [`BuildKit`](https://docs.docker.com/build/buildkit/) container started:

```console
docker run -d --name buildkitd --privileged moby/buildkit:latest
export KRAFTKIT_BUILDKIT_HOST=docker-container://buildkitd
```

Then you can run, as `root`:

```console
kraft net create -n 172.44.0.1/24 virbr0
kraft run -M 256M --network bridge:virbr0 --plat qemu --arch x86_64 --kernel-arg "vfs.fstab=[ initrd:/:initrd::: ]" .
```

If you use `sudo`, make sure you pass the `KRAFTKIT_BUILDKIT_HOST` variable to the `kraft run` command:

```console
sudo KRAFTKIT_BUILDKIT_HOST=docker-container://buildkitd kraft run -M 256M --network bridge:virbr0 --plat qemu --arch x86_64 --kernel-arg "vfs.fstab=[ initrd:/:initrd::: ]" .
```

Query the server using:

```console
curl 172.44.0.2:8080
```

You will get a `Hello, World!` message.

## Learn More

- [Unikraft Documentation](https://unikraft.org/docs/cli)
- [How to build `Dockerfile` root filesystems with `BuildKit`](https://unikraft.org/docs/getting-started/integrations/buildkit)
