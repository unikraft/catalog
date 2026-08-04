# Ntfy

This directory contains the [ntfy](https://ntfy.sh/) runtime on Unikraft, in binary compatibility mode.
It implements a simple, HTTP-based pub-sub notification service that allows you to send push notifications to your phone or desktop via PUT/POST requests, running entirely on Unikraft.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -p 8080:80 -v /tmp:/tmp --plat qemu --arch x86_64 -M 256M unikraft.org/ntfy:latest
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, the Unikraft instance will listen internally on port `80` (mapped to `8080` on your host) and wait for connections.

**Note:** To keep the Unikernel extremely lightweight and avoid massive Node.js/React dependencies, the graphical web UI is bypassed. You interact directly with the core Ntfy API via the terminal.

To verify that the server is running and successfully processing messages, open a new terminal window and send a push notification to a topic (e.g., `test`) using `curl`:

```bash
curl -d "Hello from Unikraft!" localhost:8080/test
```

You should immediately receive a JSON response from the Unikernel confirming that the payload was processed and saved, looking similar to this:

```json
{"id":"EHmxKOCNDYre","time":1774517227,"expires":1774560427,"event":"message","topic":"test","message":"Hello from Unikraft!"}
```

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps -a
```

```text
NAME        KERNEL                      ARGS                                      CREATED         STATUS    MEM     PORTS                   PLAT
kind_ozzie  project://ntfy:qemu/x86_64  /usr/bin/ntfy serve -c /etc/ntfy/serv...  15 seconds ago  running   256M    0.0.0.0:8080->80/tcp    qemu/x86_64
```

The instance name is `kind_ozzie`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm kind_ozzie
```

## Build and Run Locally

The commands so far used the pre-built Ntfy image available in the Unikraft registry.

In order to build a local Ntfy image, clone this repository and `cd` into this directory.
Then use `kraft` to build an image locally:

```bash
kraft build --no-cache --no-update --plat qemu --arch x86_64
```

Similar to the `kraft run` command, if the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

In order to run the locally built image, use `.` (*dot*, the current directory) as the final argument to the `kraft run` command:

```bash
kraft run --rm -p 8080:80 -v /tmp:/tmp --plat qemu --arch x86_64 -M 256M .
```

Same as above, it will open port `8080` and wait for connections.

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [How to build `Dockerfile` root filesystems with BuildKit](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
