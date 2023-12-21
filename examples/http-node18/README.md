# NodeJS 18 Web Server on Unikraft

This directory contains an example NodeJS 18 HTTP server.

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli).

Then, clone this repository and cd into this directory.
You can then start the NodeJS 18 HTTP server Unikraft unikernel via:

```
kraft run -p 8080:8080 -M 512Mi .
```

Once executed you will be able to view the welcome page at http://localhost:8080.

## Learn more

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [How to build `Dockerfile` root filesystems with BuildKit](https://unikraft.org/docs/getting-started/integrations/buildkit)
