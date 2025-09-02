# Prometheus 2.53

This directory contains the definition for the image running prometheus.

## Prerequisites

* Install Unikraft's CLI toolchain:

```console
curl -sSL https://unikraft.org/install | console
```
* On the host, ensure you have a backend HTTP service reachable (e.g. a Python server listening on port `5000`).

## Configure Prometheus

Modify configuration by changing the `prometheus.yml` file.

### Build and Run

1. **Create a network interface bridge**:

    ```console
    kraft net create -n 172.44.0.1/24
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
       -p 9090:9090 .
    ```

## See also

* [Unikraft CLI: Running Unikernels Locally](https://unikraft.org/docs/cli/running)
* [Traefik Configuration Reference](https://doc.traefik.io/traefik/)
