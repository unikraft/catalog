# Simple WebSocket Server

This directory contains a basic socket server example running on Unikraft. While this is a simplified implementation that doesn't fully implement the WebSocket protocol, it demonstrates the fundamentals of socket communication that would be used in a WebSocket server.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -p 8080:8080 --plat qemu --arch x86_64 .
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

The `-p 8080:8080` flag maps port 8080 from the host to port 8080 in the unikernel.

## Testing the Server

You can test the server using a simple HTTP request:

```bash
curl http://localhost:8080
```

Or use a WebSocket client for basic connection testing:

```bash
# Using websocat (https://github.com/vi/websocat)
websocat ws://localhost:8080
```

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME       KERNEL                          ARGS               CREATED         STATUS   MEM  PORTS                 PLAT
sharp_hua  oci://unikraft.org/base:latest  /websocket_server  16 seconds ago  running  64M  0.0.0.0:8080->808...  qemu/x86_64

```

To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm <instance-name>
```

Note that depending on how you modify this example your instance may need more memory to run.
To do so, use the `kraft run`'s `-M` flag, for example:

```bash
kraft run --rm -p 8080:8080 --plat qemu --arch x86_64 -M 256M .
```

## Extending This Example

This is a minimal example that demonstrates socket communication. To build a full WebSocket server, you would need to:

1. Implement the WebSocket handshake protocol
2. Add frame parsing and construction
3. Handle ping/pong for connection maintenance
4. Implement proper message framing

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
- [WebSocket Protocol RFC6455](https://tools.ietf.org/html/rfc6455)