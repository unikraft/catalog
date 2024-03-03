# Simple Python HTTP Server

This directory contains a simple [Python](https://www.python.org/) HTTP server.
The image opens up a simple HTTP server and provides a simple response to each request.

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run -M 512M -p 8080:8080 --plat qemu --arch x86_64
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it default to the CPU architecture of your system.

Once executed, it will open port `8080` and wait for connections, and it can be queried.

Query the Unikraft instance using:

```bash
curl localhost:8080
```

It will print a "Hello, World!" message.

You can list information about the Unikraft instance, use:

```bash
kraft ps
```
```text
NAME           KERNEL                          ARGS                             CREATED         STATUS   MEM   PLAT
musing_julius  oci://unikraft.org/python:3.12  /usr/bin/python3 /app/server.py  10 minutes ago  running  0MiB  qemu/x86_64
```

The instance name is `musing_julius`.
To close the Unikraft instance, use:

```bash
kraft rm musing_julius
```

Note that closing the `kraft run` command (such as using `Ctrl+c`) does not close the Unikraft instance.
If you want the Unikraft instance closed when closing the `kraft run` command, use the `--rm` option:

```bash
kraft run --rm -M 512M -p 8080:8080 --plat qemu --arch x86_64
```
