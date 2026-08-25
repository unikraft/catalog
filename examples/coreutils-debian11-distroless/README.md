# Linux Coreutils - Distroless

This directory contains a minimal Debian instance featuring core utilities such as `ls`, `cat`, `pwd`, etc., running on Unikraft.
It utilizes a Distroless container image (`base-debian12`) to provide a minimal, secure root filesystem containing only the required runtime dependencies.

## Distroless Build

For this example's needs, the chosen distroless image provides:

- The standard `/etc` directory
- The dynamic linker `ld-linux-x86-64`
- The libraries `libc`

The remaining dependencies still need to be copied manually on top of that (see `Dockerfile`).

## Set Up

Use `kraft` to run the image and start a Unikraft instance:

```console
kraft run --rm --plat qemu --arch x86_64 -M 128M -K Kraftfile.<cmd> .
```

Where `<cmd>` is the command you want to execute.

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, you should see the output of the requested command.

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
