# Running helloworld-c with urunc

This example can be packaged as an OCI image for [urunc](https://github.com/urunc-dev/urunc), the CNCF unikernel container runtime. urunc treats `hyperlight-unikraft` as a host-level VMM (like QEMU), with the OCI image carrying the Unikraft kernel and initrd payload.

## Prerequisites

- `hyperlight-unikraft` installed on the host (the VMM)
- `urunc` and `containerd-shim-urunc-v2` installed on the host
- `/dev/kvm` available
- `containerd` running

## Build

```bash
just urunc-image
```

This builds the kernel via `kraft`, compiles `hello.c` into a static-PIE binary packed as a CPIO initrd, and produces a `hello-hyperlight-unikraft:latest` Docker image.

A pre-built image is also available at `ghcr.io/hyperlight-dev/hyperlight-unikraft/hello-hyperlight-unikraft:latest`.

## Run

```bash
# Import into containerd
docker save hello-hyperlight-unikraft:latest -o /tmp/hello.tar
sudo ctr images import /tmp/hello.tar

# Run via urunc
sudo ctr run --rm --runtime io.containerd.urunc.v2 \
  docker.io/library/hello-hyperlight-unikraft:latest hello-test
```

## How it works

The OCI image contains just three files:

- `/unikernel/kernel` — Unikraft kernel ELF (built for the Hyperlight platform)
- `/unikernel/initrd.cpio` — CPIO archive containing `/bin/hello` (static-PIE C binary)
- `/urunc.json` — urunc annotations identifying this as a `hyperlight` + `unikraft` workload

When urunc runs the image, it finds `hyperlight-unikraft` on the host, bind-mounts it along with `/dev/kvm` into an isolated rootfs, and execs:

```
hyperlight-unikraft /unikernel/kernel --initrd /unikernel/initrd.cpio --memory <bytes>
```

This boots a Hyperlight micro-VM running Unikraft, which mounts the initrd and executes the hello binary.
