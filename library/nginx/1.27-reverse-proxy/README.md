# Nginx 1.25

This directory contains the definition for the `unikraft.org/nginx:1.25` image running Nginx.

To run this image, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli) and then you can run:

```console
kraft run -p 8080:80 unikraft.org/nginx:1.25
```

Query the server using:

```console
curl localhost:8080
```

You will get a simple index web page from Nginx.

## See also

- [How to run unikernels locally in Unikraft's Documentation](https://unikraft.org/docs/cli/running).
