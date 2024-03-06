# Redis 7.0 Image

This directory contains the definition for the `unikraft.org/redis:7.0` image.

Before you run image, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli).

To build and run image locally:

```
kraft build
kraft run -p 6379:6379 -M 128M
```

To fetch and run prebuilt image:

```
kraft run -p 6379:6379 unikraft.org/redis:7.0 -M 128M
```

Once executed you will be able to view connect with the Redis client:

```
redis-cli -h localhost
```

You can test it using set/get commands:

```
127.0.0.1:6379> set a 1
OK
127.0.0.1:6379> get a
"1"
127.0.0.1:6379>
```

## See also

- [How to run unikernels locally in Unikraft's Documentation](https://unikraft.org/docs/cli/running).
