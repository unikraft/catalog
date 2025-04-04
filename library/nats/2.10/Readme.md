# NATS 2.10

### Build
To build and run this image, [install Unikraft's companion command-line toolchain `kraft`](https://unikraft.org/docs/cli) and then you can run:

```console
kraft build --no-cache --no-update --log-type basic --log-level debug --plat qemu --arch x86_64 .
```

### Run
As `root`, create a network interface bridge

```console
kraft net create -n 172.44.0.1/24 virbr0
```

Run as `root` 
```console
kraft run --network virbr0 --log-type basic --log-level debug -M 256M -p 4222:4222 -p 6222:6222 -p 8222:8222 .
```

### Test
Connect to the server using `netcat`:

```console
$ nc -zv 172.44.0.2 4222
Connection to localhost 4222 port [tcp/*] succeeded! 
```

or querry the http server

```console
curl 172.44.0.2:8222
```