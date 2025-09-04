# Node21 WebSocket Server

This directory contains a Node21 WebSocket echo server implementation running on Unikraft.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository, and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance locally:

```bash
kraft run --rm -p 8080:8080 --plat qemu --arch x86_64 -M 512M .
```

If the `--plat` argument is left out, it defaults to `qemu`.  
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once running, it will open port `8080` and listen for WebSocket connections.

To test it, you can use a WebSocket client like [`wscat`](https://github.com/websockets/wscat).

Install `wscat` globally with `npm`:

```bash
npm install -g wscat
```

Then connect to the WebSocket server:

```bash
wscat --connect ws://localhost:8080
```

After connecting, you can enter messages, and the server will echo them back.

```bash
Connected (press CTRL+C to quit)
< Connection received. Waiting for messages.
> Hello
< Hello
> From
< From
> Unikraft
< Unikraft 
```

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

To stop the Unikraft instance, use `Ctrl+C` or:

```bash
kraft rm <INSTANCE_NAME>
```

## Note on Memory

Depending on the size of your application, you may need to allocate more memory. You can do this by adjusting the `-M` flag:

```bash
kraft run -p 8080:8080 --plat qemu --arch x86_64 -M 1024M .
```

## `kraft` and `sudo`

Mixing `kraft` with `sudo` can lead to unexpected behavior. Learn how to avoid using `sudo` with `kraft`:

[https://unikraft.org/sudoless](https://unikraft.org/sudoless)

## Learn More

- [WebSocket (Wikipedia)](https://en.wikipedia.org/wiki/WebSocket)
- [`ws` – A Node.js WebSocket library](https://github.com/websockets/ws)
- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with BuildKit](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
