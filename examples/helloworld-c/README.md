# Simple "Hello, world!" C Program on Unikraft

This directory contains an example C-based "Hello, world!" example.

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli).

Then, clone this repository and cd into this directory.
You can then build the project with:

```
kraft build
```

In the above command, `kraft build` will prompt you with the target you wish to compile for.
If you are unsure, select `qemu/` and your host's architecture, e.g. `qemu/x86_64`.

Once built, you can execute the unikernel via:

```
kraft run
```

## Learn more

- [How to build unikernels](https://unikraft.org/docs/cli/building)
- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [The `Kraftfile` specification](https://unikraft.org/docs/cli/reference/kraftfile/latest)
