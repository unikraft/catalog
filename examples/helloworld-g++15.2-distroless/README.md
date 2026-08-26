
# C++ "Hello, World!" - Distroless

This directory contains a C++-based "Hello, World!" example running on Unikraft with a Distroless runtime environment.

The example is based on the `helloworld-g++15.2` catalog example and uses a multi-stage Dockerfile. The application is compiled with GCC 15.2, and the resulting executable is packaged using the `gcr.io/distroless/cc:latest` runtime image.

## Set Up

To run this example, install Unikraft's companion command-line toolchain, `kraft`, clone this repository, and change into this directory.

You also need Docker, which is used by KraftKit to build the root filesystem from the Dockerfile.

## Run and Use

Use `kraft` to build the root filesystem and start a Unikraft instance:

```bash
kraft run --rm --plat qemu --arch x86_64 -M 128M .
```

The `--plat qemu` argument selects QEMU as the platform, while `--arch x86_64` selects the x86_64 architecture.

The `-M 128M` option allocates 128 MB of memory to the Unikraft instance. This amount of memory is required for the Distroless variant to successfully extract and boot the generated root filesystem in the tested configuration.

Once the instance starts successfully, the following output should be displayed:

```text
Powered by Unikraft Ijiraq (0.21.0~f06a58d)

Bye, World!
```

## Distroless Runtime

Unlike a traditional Linux distribution, the runtime image used by this example is based on the Distroless C++ image:

```text
gcr.io/distroless/cc:latest
```

The Distroless runtime does not include a shell, package manager, or other general-purpose command-line utilities. Only the runtime environment required by the application is included.

The Dockerfile uses two stages:

1. A `gcc:15.2.0-bookworm` builder stage compiles `helloworld.cpp`.
2. The resulting `/helloworld` executable is copied into the Distroless C++ runtime image.

The resulting filesystem is then used as the root filesystem of the Unikraft unikernel.

## Verify the Application with Docker

The generated Distroless image can also be tested independently from Unikraft.

Build the image:

```bash
docker build -t helloworld-g15-distroless .
```

Run the application directly from the Distroless image:

```bash
docker run --rm helloworld-g15-distroless /helloworld
```

The expected output is:

```text
Bye, World!
```

The Distroless image intentionally does not provide an interactive shell. For example, attempting to start `/bin/sh` is expected to fail because the shell is not included in the image.

## Inspect and Close

To list running Unikraft instances, use:

```bash
kraft ps
```

If the instance was not started with `--rm`, it can be stopped and removed with:

```bash
kraft rm <instance-name>
```

When `kraft run` is executed with `--rm`, the instance is automatically removed after it exits.

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.

For information about running `kraft` without `sudo`, see:

[https://unikraft.org/sudoless](https://unikraft.org/sudoless)

## Learn More

* How to run unikernels locally: [https://unikraft.org/docs/cli/running](https://unikraft.org/docs/cli/running)
* Building `Dockerfile` images with BuildKit: [https://unikraft.org/guides/building-dockerfile-images-with-buildkit](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
