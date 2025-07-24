# OpenArena

This directory contains the build definition for the [OpenArena](https://openarena.ws/news.html) image, a gaming server.

## Build and Run Locally

In oder to to build a local image, clone this repository and `cd` into this directory.
Then use `kraft` to build an image locally:

```bash
kraft build --no-cache --no-update --plat qemu --arch x86_64 .
```

Similar to the `kraft run` command, if the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

In order to run the locally built image, use `.` (_dot_, the current directory)  as the final argument to the `kraft run` command:

```bash
kraft run --rm -M 2048M -p 27960:27960/udp --plat qemu --arch x86_64 .
```

It will open port `27960` and wait for connections on the localhost.