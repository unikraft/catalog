# Node 25 Web Server

This directory contains a Node.js 25 web server running on Unikraft using a minimal distroless-style root filesystem.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to build and run the image and start a Unikraft instance:

```bash
kraft run --rm -p 8080:8080 --plat qemu --arch x86_64 -M 1024M .
```

If the `--plat` argument is left out, it defaults to `qemu`.

If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `8080` and wait for connections.

To test it, you can use `curl`:

```bash
curl localhost:8080
```

You should see a `Bye, World!` message.

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm <instance-name>
```

Note that depending on how you modify this example, your instance may need more memory to run. To increase the allocated memory, use the `kraft run` `-M` flag, for example:

```bash
kraft run -p 8080:8080 --plat qemu --arch x86_64 -M 2048M .
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.

Read more about how to start `kraft` without `sudo` at [Running KraftKit without sudo](https://unikraft.org/sudoless).

## Learn More

* [How to run unikernels locally](https://unikraft.org/docs/cli/running)
* [Building Dockerfile Images with BuildKit](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
