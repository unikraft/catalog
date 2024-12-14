# Operating Systems Tests

This directory contains test programs featuring Operating Systems concepts for Unikraft.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm --plat qemu --arch x86_64 -M 256M -K app/Kraftfile
```

Where `app` is the name of the program you want to start.

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, you should see the program's output.

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME           KERNEL                          ARGS         CREATED        STATUS   MEM   PORTS  PLAT
eloquent_koko  oci://unikraft.org/base:latest  /allocation  7 seconds ago  running  244M         qemu/x86_64
```

The instance name is `eloquent_koko`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm eloquent_koko
```

Note that depending on how you modify these examples your instance **may** need more memory to run.
To do so, use the `kraft run`'s `-M` flag, for example:

```bash
kraft run --rm --plat qemu --arch x86_64 -M 512M -K app/Kraftfile
```

Where `app` is the name of the program you want to start.

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
