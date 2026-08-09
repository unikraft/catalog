# MicroPython 1.24

This directory contains the definition for the `unikraft.org/micropython:1.24` image running MicroPython.

To run this image, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli) and then you can run:

```console
kraft run unikraft.org/micropython:1.24 -M 768M
```

Once executed, it will print:

```console
"Hello, World!"
```

You will get a simple "Hello, World!" from MicroPython.

## See also

- [How to run unikernels locally in Unikraft's Documentation](https://unikraft.org/docs/cli/running).