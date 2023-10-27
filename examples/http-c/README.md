# Simple HTTP C Server on Unikraft

This directory contains a simple HTTP server written in C running with Unikraft.
The image opens up a simple HTTP server and provides a simple HTML response for each request.

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli).

Then, clone this repository and `cd` into this directory.
You can then build the project with:

```console
kraft build
```

In the above command, `kraft build` will prompt you with the target you wish to compile for.
If you are unsure, select `qemu/` and your host's architecture, e.g. `qemu/x86_64`.

Once built, you can execute the unikernel via:

```console
kraft run -p 8080:8080
```

Once executed, query the simple HTTP server:

```console
curl localhost:8080
```

## Learn more

- [How to build unikernels](https://unikraft.org/docs/cli/building)
- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [The `Kraftfile` specification](https://unikraft.org/docs/cli/reference/kraftfile/latest)
