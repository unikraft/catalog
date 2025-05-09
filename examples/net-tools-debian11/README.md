# Unikraft `net-tools` port

This is a port of `net-tools` for Unikraft as an `examples` category.
Please note some of the applications ported are not fully functional, due to some kernel level functionalities not being yet implemented by Unikraft.
This port is mainly used to showcase the capabilities of running network applications on Unikraft.
It is unlikely there will a real use case for them.

This port contains:

- `curl`
- `dig`
- `host`
- `netcat`
- `mtr`
- `nslookup`
- `ping`
- `traceroute`
- `wget`

In order to use these applications, please modify the `Kraftfile` `cmd` variable to set the program arguments.

# Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance.
Inside the `net-tools/` directory, run:

```bash
cd <program-name>
kraft run --rm --plat qemu --arch x86_64 -W -M 256M
```

where `<program-name>` is the name of the directory of the program you want to run (e.g., `ping/`).

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, you should see the program's output.

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME           KERNEL                          ARGS         CREATED        STATUS   MEM  PORTS  PLAT
eloquent_koko  oci://unikraft.org/base:latest  /allocation  7 seconds ago  running  64M         qemu/x86_64
```

The instance name is `eloquent_koko`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm eloquent_koko
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)

> [!CAUTION]
> Some of the applications may not work as expected due to the lack of certain kernel functionalities in Unikraft.
> This is a work in progress and we are working on adding more functionalities to Unikraft.
