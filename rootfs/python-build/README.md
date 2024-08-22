# Python Docker Custom Build

This is a Docker custom build of Python.
It builds the Python interpreter from source and creates the minimal Docker image / filesystem required to run the interpreter.
The resulting image can be run via Docker or with Unikraft.

## Build and Run Docker Image

Build the Docker image by running:

```console
make
```

Check out the resulting image:

```console
$ docker image ls python-build
REPOSITORY     TAG       IMAGE ID       CREATED      SIZE
python-build   latest    cd6e9e5e2bab   6 days ago   61.4MB
```

Start a temporary Python container by using:

```console
$ make start_anon
docker run --rm --interactive --tty python-build
Python 3.12.0 (main, Oct 20 2023, 22:28:28) [GCC 11.4.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>>
```

You can then run Python commands at the prompt.

## Export and Use Docker Filesystem

You can also export the Docker filesystem:

```console
make export
```

The entire filesystem is going to be exported to the `rootfs/` directory:

```console
rootfs/
|-- dev/
|-- etc/
|-- lib/
|-- lib64/
|-- proc/
|-- sys/
`-- usr/
```

You can then check out the filesystem, by runing the Python interpreter in a `chroot` environment:

```console
sudo chroot rootfs/ /usr/local/bin/python3
```

## Python Version Update

You can update the Python version being built and used by editing the corresponding variable in the `Makefile`:

```
PYTHON_VERSION = 3.12.0
```
