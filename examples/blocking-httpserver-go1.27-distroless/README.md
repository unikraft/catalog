# Go Blocking HTTP Server - Distroless

This example demonstrates running a blocking Go 1.27 HTTP server on Unikraft.
It uses raw syscalls for accept/read/write, embeds its rootfs at build time, and includes `wrk` and `vegeta` load-test helpers.

## Distroless Build

For this example's needs, the chosen distroless image (`gcr.io/distroless/cc-debian12`) provides:

- The dynamic linker `ld-linux-x86-64`
- The library `libc`

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Build the unikernel using `kraft`:

```bash
UK_CFLAGS="-std=gnu17 -Wno-error=incompatible-pointer-types" kraft build --plat qemu --arch x86_64 .
```

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -p 8080:8080 --plat qemu --arch x86_64 -M 256M .
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `8080` and wait for connections.
To test it, you can use `curl`:

```bash
curl localhost:8080
```

You should see an HTML response containing "Hello from Unikraft".

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME                 KERNEL                                                       ARGS         CREATED         STATUS   MEM   PORTS                   PLAT
recursing_panpanzee  project://blocking-httpserver-go1-27-distroless:qemu/x86_64  /bin/server  23 seconds ago  running  256M  0.0.0.0:8080->8080/tcp  qemu/x86_64
```

The instance name is `recursing_panpanzee`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm recursing_panpanzee
```

Note that depending on how you modify this example your instance **may** need more memory to run.
To do so, use the `kraft run`'s `-M` flag, for example:

```bash
kraft run --rm -p 8080:8080 --plat qemu --arch x86_64 -M 512M .
```

## Load Testing

Two load-test Shell scripts are provided in this directory.
The server must be running before triggering any of these scripts.

For `wrk`:

```bash
./bench_wrk.sh
```

For `vegeta`:

```bash
./bench_vegeta.sh
```

Example output:

```bash
[2026-08-27 15:43:11] vegeta load test against http://127.0.1:8080

[2026-08-27 15:43:11] === GET / ===
[2026-08-27 15:43:11] vegeta: GET http://localhost:8080/
[2026-08-27 15:43:11]   rate=100/s  duration=10s  workers=4
Requests      [total, rate, throughput]         1000, 100.10, 62.46
Duration      [total, attack, wait]             16.009s, 9.99s, 6.019s
Latencies     [min, mean, 50, 90, 95, 99, max]  691.769µs, 202.724ms, 1.507ms, 1.996ms, 2.129ms, 6.192s, 6.389s
Bytes In      [total, mean]                     147000, 147.00
Bytes Out     [total, mean]                     0, 0.00
Success       [ratio]                           100.00%
Status Codes  [code:count]                      200:1000
Error Set:

[2026-08-27 15:43:27] === POST /wrk ===
[2026-08-27 15:43:27] vegeta: POST http://localhost:8080/wrk
[2026-08-27 15:43:27]   rate=100/s  duration=10s  workers=4
[2026-08-27 15:43:27]   body="hello from vegeta" (17 bytes)
Requests      [total, rate, throughput]         1000, 100.10, 64.41
Duration      [total, attack, wait]             15.525s, 9.99s, 5.535s
Latencies     [min, mean, 50, 90, 95, 99, max]  735.887µs, 522.198ms, 2.006ms, 8.677ms, 5.705s, 5.974s, 6.028s
Bytes In      [total, mean]                     22000, 22.00
Bytes Out     [total, mean]                     17000, 17.00
Success       [ratio]                           100.00%
Status Codes  [code:count]                      200:1000
Error Set:

[2026-08-27 15:43:43] Done
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
