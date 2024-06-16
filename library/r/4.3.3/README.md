# R 4.3.3

This directory contains the definition for the `unikraft.org/r:4.3.3` image running R.

To run this image, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli) and then you can run:

```console
kraft run unikraft.org/r:4.3.3 -M 768M
```

Once executed, it will print:

```console
[1] "Hello, World!"
```

You will get a simple "Hello, World!" from R.

## See also

- [How to run unikernels locally in Unikraft's Documentation](https://unikraft.org/docs/cli/running).
