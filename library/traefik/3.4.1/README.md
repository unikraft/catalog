# Traefik 3.4.1 Image

This directory contains the definition for the `unikraft.org/traefik:3.4.1` image running the Traefik reverse proxy and load balancer.

## Prerequisites

* Install Unikraft’s CLI toolchain:

  ```console
  curl -sSL https://unikraft.org/install | console
  ```
* On the host, ensure you have a backend HTTP service reachable (e.g. a Python server listening on port `5000`).

## Configure Traefik

Modify configuration by changing the `traefik.yml` and `dynamic.yml` files:


## Build and Run

1. **Create a network interface bridge**:

   ```console
   kraft net create -n 172.44.0.1/24 virbr0
   ```
2. **Build the unikernel** (from this directory):

   ```console
   kraft build --no-cache --plat qemu --arch x86_64 .
   ```
3. **Run the unikernel** (as root):

   ```console
   kraft run \
       --network virbr0 \
       -M 4096M \
       -p 80:80 .
   ```

By default, this will listen on port **80** for HTTP traffic and port **8080** for the Traefik dashboard.

## Testing

* Ensure your backend service (e.g. Python server) is listening on **0.0.0.0:5000** on the host.
* From the host, subscribe or send test requests:

  ```bash
  curl http://172.44.0.2/
  ```

> **Note:** Replace `172.44.0.2` with the IP assigned to the unikernel, as shown in its console output.

## Customization

* To use HTTPS, configure TLS certificates in `dynamic.yml` and add an `entryPoints.websecure` section in `traefik.yml`.
* Adjust router rules in `dynamic.yml` for host-based or path-based routing as needed.

## Limitations

* **File watch mode (`watch: true`)** is not supported in Unikraft unikernels; the current image requires watch: false.
* **Dashboard (`api.dashboard: true`)** is currently not supported in this unikernel image; set `dashboard: false`.

## See also

* [Unikraft CLI: Running Unikernels Locally](https://unikraft.org/docs/cli/running)
* [Traefik Configuration Reference](https://doc.traefik.io/traefik/)
