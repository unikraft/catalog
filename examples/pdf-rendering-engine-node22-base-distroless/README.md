# Node 22 PDF Rendering Engine - Chainguard Distroless

This directory contains a Node 22 PDF Rendering Engine implementation using [`ExpressJS`](https://expressjs.com/) and [`pdfkit`](https://pdfkit.org/) running on Unikraft. It uses a securely pinned version of the `cgr.dev/chainguard/node` base image. This environment provides a natively PIE-compiled Node.js binary compatible with Unikraft, demonstrating advanced binary compatibility by rendering documents natively in memory without relying on headless browsers or external dynamic libraries.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -p 3000:3000 --plat qemu --arch x86_64 -M 1024M .
```

If the `--plat` argument is left out, it defaults to `qemu`.

If the `--arch` argument is left out, it defaults to your system's CPU architecture.

If the `-M` argument (memory allocation) is left out, it defaults to 64M. Explicitly setting it to `-M 1024M` provides enough memory for the V8 engine startup and the PDF generation process, ensuring the unikernel boots successfully.

Once executed, it will open port `3000` and wait for connections.

To generate a PDF, open a new terminal and send a POST request with a JSON payload:

```bash
curl -X POST http://localhost:3000/render \
  -H "Content-Type: application/json" \
  -d '{"title": "Factura 001", "content": "Total de plata: 1500 RON"}' \
  --output factura.pdf
```

Open the newly created `factura.pdf` file with any standard PDF viewer to validate the rendering.

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME                 KERNEL                          ARGS                          CREATED        STATUS   MEM    PORTS                    PLAT
mystifying_gregoire  oci://unikraft.org/base:latest  /usr/bin/node /app/index.js   8 seconds ago  running  488M   0.0.0.0:3000->3000/tcp   qemu/x86_64
```

The instance name is `mystifying_gregoire`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm mystifying_gregoire
```

Note that depending on how you modify this example your instance **may** need more memory to run.
To do so, use the `kraft run`'s `-M` flag:

```bash
kraft run -p 3000:3000 --plat qemu --arch x86_64 -M 2048M .
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
