# Imaginary

This directory contains the [Imaginary](https://github.com/h2non/imaginary) runtime on Unikraft, in binary compatibility mode.
It implements Imaginary running on Unikraft.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -p 8080:8080 --plat qemu --arch x86_64 -M 512M unikraft.org/imaginary:1.2
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `8080` and wait for connections.
To test it, you can use `curl` to get the health status:

```console
curl -s localhost:8080/health | jq
```

You will get a on output such as:

```text
{
  "uptime": 86,
  "allocatedMemory": 0.19,
  "totalAllocatedMemory": 0.39,
  "goroutines": 6,
  "completedGCCycles": 2,
  "cpus": 1,
  "maxHeapUsage": 3.66,
  "heapInUse": 0.19,
  "objectsInUse": 890,
  "OSMemoryObtained": 7.48
}
```

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME           KERNEL                           ARGS                                           CREATED        STATUS   MEM   PORTS                   PLAT
wizardly_moja  project://imaginary:qemu/x86_64  /usr/bin/imaginary -p 8080 -enable-url-source  2 minutes ago  running  488M  0.0.0.0:8080->8080/tcp  qemu/x86_64
```

The instance name is `wizardly_moja`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm wizardly_moja
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
kraft run --rm -p 8080:8080 --plat qemu --arch x86_64 -M 512M .
```

Same as above, it will open port `8080` and wait for connections.

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [How to build `Dockerfile` root filesystems with BuildKit](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
