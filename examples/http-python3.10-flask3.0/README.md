# Flask 3.0 Web Server on Unikraft

This directory contains an example [Flask 3.0](https://flask.palletsprojects.com/en/3.0.x/) HTTP server.

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli).

Then, clone this repository and cd into this directory.
You can then start the Flask 3.0 HTTP server Unikraft unikernel via:

```
kraft run -p 8000:8000 -M 512Mi .
```

Once executed you will be able to view the welcome page at http://localhost:8000.

## Learn more

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [How to build `Dockerfile` root filesystems with BuildKit](https://unikraft.org/docs/getting-started/integrations/buildkit)
