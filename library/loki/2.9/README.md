# Loki

This directory contains the [Loki](https://grafana.com/oss/loki/) log aggregation system on Unikraft, in binary compatibility mode.
It implements a Loki instance running on Unikraft.

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft run --rm -M 2048M -p 3100:3100 --plat qemu --arch x86_64 unikraft.org/loki:2.9
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, it will open port `3100` and wait for connections.
To test it, you can use `curl`:

```bash
curl localhost:3100/ready
```

You should see "ready" response from Loki.

## Push Logs

To push logs to Loki, you can use the following curl command:

```bash
curl -v -H "Content-Type: application/json" -XPOST "http://localhost:3100/loki/api/v1/push" --data-raw \
  '{"streams": [{ "stream": { "foo": "bar2" }, "values": [ [ "1570818238000000000", "fizzbuzz" ] ] }]}'
```

## Query Logs

To query logs from Loki:

```bash
curl -G -s "http://localhost:3100/loki/api/v1/query" --data-urlencode 'query={foo="bar2"}' | jq
```

## Inspect and Close

To list information about the Unikraft instance, use:

```bash
kraft ps
```

To close the Unikraft instance, close the `kraft` process (e.g., via `Ctrl+c`) or run:

```bash
kraft rm <instance_name>
```

## Build and Run Locally

To build a local image, clone this repository and `cd` into this directory.
Then use `kraft` to build an image locally:

```bash
kraft build --no-cache --no-update --plat qemu --arch x86_64
```

In order to run the locally built image, use `.` as the final argument:

```bash
kraft run --rm -M 2048M -p 3100:3100 --plat qemu --arch x86_64 .
```

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [Loki Documentation](https://grafana.com/docs/loki/latest/)
