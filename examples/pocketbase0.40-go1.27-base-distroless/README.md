# Go PocketBase Backend - Distroless

This directory contains a [`PocketBase`](https://pocketbase.io/) backend system running on Unikraft.
It utilizes a Distroless container image (`gcr.io/distroless/static-debian13`) to provide a minimal, secure root filesystem containing only the required runtime dependencies.

## Distroless Build

For this example's needs, the chosen distroless image provides:

- CA certificates (`ca-certificates`)
- Timezone data (`tzdata`)
- Standard `/tmp` and `/etc` directories

## Set Up

To run this example, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli), clone this repository and `cd` into this directory.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -p 8080:8080 --plat qemu --arch x86_64 -M 256M .
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `8080` and wait for connections.

To test the REST API endpoint health, you can use `curl`:

```bash
curl localhost:8080/api/health
```

You should see the message:

```JSON
{"message":"API is healthy.","code":200,"data":{}}
```

To test the app's dashboard, you can also use `curl`:

```bash
curl localhost:8080/_/
```

You should see PocketBase's landing page in HTML format.

To interact with the app in the browser, you must perform the initial "superuser" login.
In the unikernel's console, you should see a message like this:

```bash
(!) Launch the URL below in the browser if it hasn't been open already to create your first superuser account:
http://0.0.0.0:8080/_/#/pbinstall/eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJjb2xsZWN0aW9uSWQiOiJwYmNfMzE0MjYzNTgyMyIsImV4cCI6MTc4OTI5Njc1NiwiaWQiOiJ1MnFxZmRnenU2dXdzaXUiLCJyZWZyZXNoYWJsZSI6ZmFsc2UsInR5cGUiOiJhdXRoIn0.3ch0oT0PTPJcjh8pruZ6iFH8HDTSdn37M8uMX6ulF9I
```

This contains PocketBase's one-time JWT token for the "superuser" account.
Access that URL in the browser, create the account and start interacting with
the dashboard and the underlying SQLite database.

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

```text
NAME            KERNEL                          ARGS                                              CREATED         STATUS   MEM   PORTS                   PLAT
goofy_faustino  oci://unikraft.org/base:latest  /server serve --http=0.0.0.0:8080 --dir=/pb_data  10 seconds ago  running  256M  0.0.0.0:8080->8080/tcp  qemu/x86_64
```

The instance name is `goofy_faustino`.
To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm goofy_faustino
```

Note that depending on how you modify this example your instance **may** need more memory to run.
To do so, use the `kraft run`'s `-M` flag, for example:

```bash
kraft run --rm -p 2015:2015 --plat qemu --arch x86_64 -M 512M .
```

## `kraft` and `sudo`

Mixing invocations of `kraft` and `sudo` can lead to unexpected behavior.
Read more about how to start `kraft` without `sudo` at [https://unikraft.org/sudoless](https://unikraft.org/sudoless).

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Building `Dockerfile` Images with `BuildKit`](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
