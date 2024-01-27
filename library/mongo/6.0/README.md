# MongoDB

This directory contains the [MongoDB](https://www.mongodb.com/) runtime on Unikraft, in binary compatibility mode.
It starts a MongoDB server instance on Unikraft.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -M 1024M -p 27017:27017 --plat qemu --arch x86_64 unikraft.org/mongo:6.0
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `27017` and wait for connections.
To test it, use the [`mongo` shell](https://www.mongodb.com/docs/v4.4/mongo/):

```bash
mongo
```

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps -a
```

```text
NAME                KERNEL                       ARGS                           CREATED        STATUS   MEM   PORTS                     PLAT
pedantic_snowflake  project://mongo:qemu/x86_64  /usr/bin/mongod --bind_ip_all  6 seconds ago  running  976M  0.0.0.0:27017->27017/tcp  qemu/x86_64
```

The instance name is `pedantic_snowflake`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm pedantic_snowflake
```

## Build and Run Locally

The commands so far used the pre-built MongoDB image available in the Unikraft registry.

In oder to to build a local MongoDB image, clone this repository and `cd` into this directory.
Then use `kraft` to build an image locally:

```bash
kraft build --no-cache --no-update --plat qemu --arch x86_64
```

Similar to the `kraft run` command, if the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

In order to run the locally built image, use `.` (_dot_, the current directory)  as the final argument to the `kraft run` command:

```bash
kraft run --rm -M 1024M -p 27017:27017 --plat qemu --arch x86_64 .
```

Same as above, it will open port `27017` and wait for connections.

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [How to build `Dockerfile` root filesystems with BuildKit](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
