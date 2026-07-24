# Traefik 3.0 Proxy on Unikraft

This directory contains an example [Traefik 3.0](https://doc.traefik.io/traefik/) Proxy.

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Prerequisites

To use this example, it is recommended to create an instance of `traefik/whoami` in a Docker container to see the effects of the app in practice.

Use the commands below to pull the image of `traefik/whoami` and run it in a container.

```bash
docker pull traefik/whoami
docker run -d -p 8000:80 --name whoami traefik/whoami
```

Note: `dynamic.yml` is configured to reach the `whoami` container via the Docker bridge IP (`http://172.17.0.1:8000`). If your bridge IP differs (or you’re on a non-Linux Docker setup), update `dynamic.yml` accordingly. You can verify your local Docker bridge IP by using the following command:

```bash
docker network inspect bridge -f '{{(index .IPAM.Config 0).Gateway}}'
```

## Run and Use

Warning: This example enables the insecure Traefik API/dashboard (`--api.insecure=true`). Do not expose the dashboard port (8081) to untrusted networks.

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -M 1G -p 8080:80 -p 8081:8080
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open ports `8080` and `8081` and wait for connections.
To test it, you can use `curl`:

```bash
curl localhost:8081/dashboard
curl -H 'Host: whoami.localhost' http://localhost:8080 # the service that Traefik exposes (in this example a whoami server written in Go)
```

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME                      KERNEL                                 ARGS                                                  CREATED         STATUS   MEM   ...
agitated_frodo            oci://unikraft.org/base:latest         /usr/local/bin/traefik --api.insecure=true --prov...  12 minutes ago  running  976M  ...
```

The instance name is `agitated_frodo`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm agitated_frodo
```

Note that depending on how you modify this example your instance **may** need more memory to run.
To do so, use the `kraft run`'s `-M` flag, for example:

```bash
kraft run --rm -M 2G -p 8080:80 -p 8081:8080
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
