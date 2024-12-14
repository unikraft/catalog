# Linux Coreutils

This directory contains a minimal Debian instance featuring core utilities such as `ls`, `cat`, `pwd`, etc., running on Unikraft.

## Set Up

Use `kraft` to run the image and start a Unikraft instance:

```console
kraft run --rm --plat qemu --arch x86_64 -K Kraftfile.<cmd> .
```

Where `<cmd>` is the command you want to execute.

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, you should see the output of the requested command.
