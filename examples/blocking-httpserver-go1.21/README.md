# Go Blocking HTTP Server Example on QEMU and Firecracker

This example demonstrates running a blocking Go 1.21 HTTP server on Unikraft using QEMU and Firecracker. The server uses raw syscalls for accept/read/write, embeds its rootfs at build time, and includes wrk and vegeta load-test helpers.

Both platforms attach to the same Kraft network (`kraft0`) with guest IP `172.44.0.2`, so the server is always reached at `http://172.44.0.2:8080`.

## Requirements

- `kraft` installed on your path.

## How to Build

1. Build the QEMU kernel (embeds rootfs from Dockerfile):
   ```bash
   just build-qemu
   ```
   Or manually:
   ```bash
   kraft build --plat qemu --arch x86_64
   ```

2. Build the Firecracker kernel (embeds rootfs from Dockerfile):
   ```bash
   just build-fc
   ```
   Or manually:
   ```bash
   kraft build --plat fc --arch x86_64
   ```
   *Note: The `Kraftfile` points `rootfs` at `./Dockerfile`, so KraftKit builds and embeds the rootfs during `kraft build`.*

## How to Run

1. Run the HTTP server on QEMU:
   ```bash
   just run-qemu
   ```
   Or manually:
   ```bash
   kraft net create --network "172.44.0.1/24" "kraft0"
   kraft run --plat qemu --rm --memory 128Mi --network kraft0:172.44.0.2 .unikraft/build/blocking-httpserver-go1-21_qemu-x86_64 --as=kernel -- /bin/server
   ```

2. Run the HTTP server on Firecracker:
   ```bash
   just run-fc
   ```
   Or manually:
   ```bash
   kraft net create --network "172.44.0.1/24" "kraft0"
   kraft run --plat fc --rm --memory 128Mi --network kraft0:172.44.0.2 .unikraft/build/blocking-httpserver-go1-21_fc-x86_64 --as=kernel -- /bin/server
   ```

   Test either platform with:
   ```bash
   curl http://172.44.0.2:8080/
   ```

3. Run wrk load test (server must be running):
   ```bash
   just wrk
   ```

4. Run vegeta load test (server must be running):
   ```bash
   just vegeta
   ```
Example output:
```bash
[i] using arch=x86_64 plat=qemu
Kernel: ".unikraft/build/blocking-httpserver-go1-21_qemu-x86_64"
Memory: 134217728 B
Serving on http://0.0.0.0:8080
```