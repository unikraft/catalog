# Simple Python HTTP Server

This directory contains a simple [Python](https://www.python.org/) HTTP server running on Unikraft.
It opens a Unikraft instance sunning simple HTTP server that provides a simple response to each request.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli).
Then, clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run -p 8080:8080 --plat qemu --arch x86_64
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it default to the CPU architecture of your system.

Once executed, it will open port `8080` and wait for connections, and it can be queried.

Query the Unikraft instance using:

```bash
curl localhost:8080
```

It will print a "Hello, World!" message.

## Inspect and Close

You can list information about the Unikraft instance, use:

```bash
kraft ps
```
```text
NAME                 KERNEL                          ARGS        CREATED         STATUS   MEM   PLAT
nostalgic_snowflake  oci://unikraft.org/python:3.10  /server.py  46 seconds ago  running  0MiB  qemu/x86_64
```

The instance name is `nostalgic_snowflake`.
To close the Unikraft instance, use:

```bash
kraft rm nostalgic_snowflake
```

Note that closing the `kraft run` command (such as using `Ctrl+c`) does not close the Unikraft instance.
If you want the Unikraft instance closed when closing the `kraft run` command, use the `--rm` option:

```bash
kraft run --rm -p 8080:8080 --plat qemu --arch x86_64
```

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [How to build `Dockerfile` root filesystems with BuildKit](https://unikraft.org/docs/getting-started/integrations/buildkit)
