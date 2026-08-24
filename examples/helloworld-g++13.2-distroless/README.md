# C++ "Hello, World!" - GCC 13.2 Distroless

This directory contains a C++-based "Hello, World!" example running on Unikraft with a Distroless runtime environment.

The example uses GCC 13.2 to compile the application and packages the resulting executable using the `gcr.io/distroless/cc-debian12` runtime image.

## Set Up

To run this example, install Unikraft's companion command-line toolchain `kraft`, clone this repository and change into this directory.

You also need Docker, which is used by KraftKit to build the root filesystem from the Dockerfile.

## Run and Use

Use `kraft` to build the root filesystem and start a Unikraft instance:

```bash
kraft run --rm --plat qemu --arch x86_64 -M 128M .
```

The --plat qemu argument selects QEMU as the platform, while --arch x86_64 selects the x86_64 architecture.

The -M 128M option allocates 128 MB of memory to the Unikraft instance.

Once the instance starts successfully, the following output should be displayed:

```bash
Bye, World!
```

Distroless Runtime

Unlike a traditional Linux distribution, the runtime image used by this example is based on the Distroless C++ image:

```bash
gcr.io/distroless/cc-debian12
```

The Distroless runtime does not include a shell, package manager, or other general-purpose command-line utilities. It contains the runtime libraries required by the application without the additional tools normally found in a general-purpose Linux distribution.

The Dockerfile uses two stages:

A gcc:13.2.0-bookworm builder stage compiles helloworld.cpp.
The resulting /helloworld executable is copied into the Distroless C++ runtime image.

The resulting filesystem is then used as the root filesystem of the Unikraft unikernel.

## Verify the Application with Docker

The Distroless image can also be built and tested independently from Unikraft:

```bash
docker build -t helloworld-g13-distroless .
```


## Run the application directly from the Distroless image:

```bash
docker run --rm helloworld-g13-distroless
```

The expected output is:

```bash
Bye, World!
```

The Distroless image intentionally does not provide an interactive shell. For example, attempting to start /bin/sh is expected to fail because the shell is not included in the image.

## Inspect and Close

To list running Unikraft instances, use:

```bash
kraft ps
```

If the instance was not started with --rm, it can be stopped and removed with:
```bash
kraft rm <instance-name>
```
When kraft run is executed with --rm, the instance is automatically removed after it exits.

## kraft and sudo

Mixing invocations of kraft and sudo can lead to unexpected behavior.

Read more about how to start kraft without sudo at:

https://unikraft.org/sudoless

## Learn More
https://unikraft.org/docs/cli/running
https://unikraft.org/guides/building-dockerfile-images-with-buildkit