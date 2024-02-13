# Redis 7.2

This directory contains the definition for the `unikraft.org/redis:7.2` image starting a Redis instance.

To run this image, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli) and then you can run:

```console
kraft run -p 6379:6379 unikraft.org/redis:7.2
```

Query the server using `redis-cli` with a set of commands such as below:

```console
$ redis-cli -h localhost
localhost:6379> ping
PONG
localhost:6379> set a 1
OK
localhost:6379> get a
"1"
```

## See also

- [How to run unikernels locally in Unikraft's Documentation](https://unikraft.org/docs/cli/running).
