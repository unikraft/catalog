# C ZeroMQ Request/Reply Server

This directory contains a C ZeroMQ Request/Reply server running on Unikraft.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -p 5000:5000 --plat qemu --arch x86_64 .
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `5000` and wait for connections. To test it you
can install the `pyzmq` Pythoon package and use the following Python code to
connect:

```python
import zmq

ctx = zmq.Context()
sock = ctx.socket(zmq.REQ)
sock.connect("tcp://localhost:5000")
sock.send(b'Hello, World!")
print(sock.recv())
```

You should see a "Hello, World!" message in the ZeroMQ console and an "ACK"
message in your Python script output.

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME              KERNEL                          ARGS                 CREATED        STATUS   MEM  PORTS                   PLAT
infallible_massa  oci://unikraft.org/base:latest  /usr/bin/zmq-server  1 seconds ago  running  64M  0.0.0.0:5000->5000/tcp  qemu/x86_64
```

The instance name is `infallible_massa`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm infallible_massa
```

Note that depending on how you modify this example your instance **may** need more memory to run.
To do so, use the `kraft run`'s `-M` flag, for example:

```bash
kraft run --rm -p 5000:5000 --plat qemu --arch x86_64 -M 256M .
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
