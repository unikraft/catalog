# NGINX 1.15 Image

This directory contains the definition for the `unikraft.org/nginx:1.15` image.

To run this image, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli) and then you can run:

```
kraft run -p 8080:80 unikraft.org/nginx:1.15
```

Once executed you will be able to view the built-in welcome page at http://localhost:8080.

To customize the static content served over NGINX, simply mount a path on your host:

```
kraft run -p 8080:80 path/to/html:/nginx/html unikraft.org/nginx:1.15
```

## See also

- [How to run unikernels locally in Unikraft's Documentation](https://unikraft.org/docs/cli/running).
