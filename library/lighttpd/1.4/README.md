# Lighttpd 1.4

This directory contains the definition for the `unikraft.org/lighttpd:1.4`
image running [lighttpd](https://www.lighttpd.net/).

To run this image, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli)
and then you can run:

```console
kraft run -p 8080:80 unikraft.org/lighttpd:1.4
```

Query the server using:

```console
curl localhost:8080
```

You will get a simple index web page served by lighttpd.

## See also

- [How to run unikernels locally in Unikraft's Documentation](https://unikraft.org/docs/cli/running).
