# Node 22 JWT Authenticator - Chainguard Distroless

This directory contains a Node 22 JWT Gatekeeper implementation using [`Hono`](https://hono.dev/) and [`jose`](https://github.com/panva/jose) running on Unikraft. It uses a securely pinned version of the `cgr.dev/chainguard/node` base image. This minimal environment lacks a shell and unnecessary system utilities, significantly reducing the attack surface while providing a natively PIE-compiled Node.js binary compatible with Unikraft.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -p 3000:3000 --plat qemu --arch x86_64 -M 1024M .
```

If the `--plat` argument is left out, it defaults to `qemu`.

If the `--arch` argument is left out, it defaults to your system's CPU architecture.

If the `-M` argument (memory allocation) is left out, it defaults to 64M. Explicitly setting it to `-M 1024M` provides enough memory for the V8 engine startup and ensures the unikernel boots successfully.

Once executed, it will open port `3000` and wait for connections.

Test the public health endpoint:

```bash
curl http://localhost:3000/health
```

To test the protected endpoint, you need a valid JWT token. The application defaults to the secret `change-me-in-production`, which can be overridden in production using the `JWT_SECRET` environment variable.

Install the local dependencies to use the generation script:

```bash
npm install
node generate.js
```

Use the generated token to access the protected route:

```bash
curl -i -H "Authorization: Bearer <TOKEN>" http://localhost:3000/protected/me
```

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME                KERNEL                          ARGS                                     CREATED        STATUS   MEM   PORTS                   PLAT
busy_pocketswarhol  oci://unikraft.org/base:latest  /usr/bin/node --max-old-space-size=6...  4 seconds ago  running  976M  0.0.0.0:3000->3000/tcp  qemu/x86_64
```

The instance name is `busy_pocketswarhol`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm busy_pocketswarhol
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
