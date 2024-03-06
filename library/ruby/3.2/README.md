# Ruby

This directory contains the [Ruby](https://www.ruby-lang.org) runtime on Unikraft, in binary compatibility mode.
It implements a simple HTTP server running on Unikraft that provides a simple response to each request.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run -M 256M -p 8080:8080 --plat qemu --arch x86_64 unikraft.org/ruby:3.2
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `8080` and wait for connections.
To test it, you can use `curl`:

```bash
curl localhost:8080
```

You should see a "Hello, World!" message.

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps -a
```

```text
NAME         KERNEL                      ARGS                          CREATED         STATUS   MEM   PORTS                   PLAT
happy_gordo  project://ruby:qemu/x86_64  /usr/bin/ruby /src/server.rb  46 seconds ago  running  0MiB  0.0.0.0:8080->8080/tcp  qemu/x86_64
```

The instance name is `happy_gordo`.
To close the Unikraft instance, use:

```bash
kraft rm happy_gordo
```

Note that closing the `kraft run` command (e.g., via `Ctrl+c`) does not kill the Unikraft instance.
If you want the Unikraft instance closed when closing the `kraft run` command, use the `--rm` option:

```bash
kraft run --rm -M 256M -p 8080:8080 --plat qemu --arch x86_64 unikraft.org/ruby:3.2
```

## Build and Run Locally

The commands so far used the pre-build Ruby image available in the Unikraft registry.

In oder to to build a local image, clone this repository and `cd` into this directory.
Then use `kraft` to build an image locally:

```bash
kraft build --no-cache --no-update --plat qemu --arch x86_64
```

Similar to the `kraft run` command, if the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

In order to run the locally built image, use `.` (_dot_, the current directory)  as the final argument to the `kraft run` command:

```bash
kraft run -M 256M -p 8080:8080 --plat qemu --arch x86_64 .
```

Same as above, it will open port `8080` and wait for connections.

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [How to build `Dockerfile` root filesystems with BuildKit](https://unikraft.org/docs/getting-started/integrations/buildkit)
