# Rust/Rocket v0.5

This example was derived from [Rocket's "hello" example](https://github.com/rwf2/Rocket/tree/v0.5/examples/hello).

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -p 8080:8080 --plat qemu --arch x86_64
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `8080` and wait for connections.
To test it, you can use `curl`.
Try one of these available endpoints:

```bash
Then try visiting one of the available paths:
- https://<NAME>.<METRO>.kraft.cloud/hello/world
- https://<NAME>.<METRO>.kraft.cloud/hello/мир
- https://<NAME>.<METRO>.kraft.cloud/wave/Rocketeer/100
- https://<NAME>.<METRO>.kraft.cloud/?emoji
- https://<NAME>.<METRO>.kraft.cloud/?name=Rocketeer
- https://<NAME>.<METRO>.kraft.cloud/?lang=ру
- https://<NAME>.<METRO>.kraft.cloud/?lang=ру&emoji
- https://<NAME>.<METRO>.kraft.cloud/?emoji&lang=en
- https://<NAME>.<METRO>.kraft.cloud/?name=Rocketeer&lang=en
- https://<NAME>.<METRO>.kraft.cloud/?emoji&name=Rocketeer
- https://<NAME>.<METRO>.kraft.cloud/?name=Rocketeer&lang=en&emoji
- https://<NAME>.<METRO>.kraft.cloud/?lang=ru&emoji&name=Rocketeer
```

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME                 KERNEL                          ARGS        CREATED         STATUS   MEM   PLAT
admiring_ndakasi     oci://unikraft.org/base:latest  /server     1 minute ago    running  64MiB  0.0.0.0:8080->8080/tcp  qemu/x86_64
```

The instance name is `nostalgic_snowflake`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm nostalgic_snowflake
```

Note that depending on how you modify this example your instance **may** need more memory to run.
To do so, use the `kraft run`'s `-M` flag, for example:

```bash
kraft run -p 8080:8080 --plat qemu --arch x86_64 -M 512M
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
