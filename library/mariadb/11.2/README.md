# MariaDB

This directory contains the [MariaDB](https://mariadb.org/) runtime on Unikraft, in binary compatibility mode.
It implements a simple HTTP server running on Unikraft that provides a simple response to each request.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -M 1024M -p 3306:3306 --plat qemu --arch x86_64 unikraft.org/mariadb:11.2
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `3306` and wait for connections.
To test it, you can use the `mysql` client.
The `root` password is configured in the `Dockerfile` to `unikraft`:

```bash
mysql -u root -punikraft -h 127.0.0.1
```

```text
Welcome to the MariaDB monitor.  Commands end with ; or \g.
Your MariaDB connection id is 4
Server version: 11.2.2-MariaDB-1:11.2.2+maria~ubu2204-log mariadb.org binary distribution

Copyright (c) 2000, 2018, Oracle, MariaDB Corporation Ab and others.

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

MariaDB [(none)]> show databases;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| mysql              |
| performance_schema |
| sys                |
+--------------------+
4 rows in set (0.001 sec)

MariaDB [(none)]> exit
```

You receive a shell that you can use to run MySQL / MariaDB commands.

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps -a
```

```text
NAME            KERNEL                         ARGS                                      CREATED        STATUS   MEM   PORTS                   PLAT
distracted_moe  project://mariadb:qemu/x86_64  /usr/sbin/mariadbd --user=root --log-bin  5 seconds ago  running  976M  0.0.0.0:3306->3306/tcp  qemu/x86_64
```

The instance name is `distracted_moe`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm distracted_moe
```

## Build and Run Locally

The commands so far used the pre-built MariaDB image available in the Unikraft registry.

In oder to to build a local MariaDB image, clone this repository and `cd` into this directory.
Then use `kraft` to build an image locally:

```bash
kraft build --no-cache --no-update --plat qemu --arch x86_64
```

Similar to the `kraft run` command, if the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

In order to run the locally built image, use `.` (_dot_, the current directory)  as the final argument to the `kraft run` command:

```bash
kraft run --rm -M 1024M -p 3306:3306 --plat qemu --arch x86_64 .
```

Same as above, it will open port `3306` and wait for connections.

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [How to build `Dockerfile` root filesystems with BuildKit](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
