# go-httpbin

This directory contains the build definition for the [httpbingo](https://httpbingo.org/) image, an HTTP request & response testing service.

## Build and Run Locally

To build the image locally, clone this repository and cd into this directory. Then run:

```console
kraft build --no-cache .
```

To run the locally built image, use:

```console
kraft run -p 8080:8080 .
```

## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```console
kraft run --rm -p 8080:8080 --plat qemu --arch x86_64 unikraft.org/httpbingo:2.13.4
```

If the `--plat` argument is left out, it defaults to `qemu`.
If the `--arch` argument is left out, it defaults to your system's CPU architecture.

Once executed, visit `http://localhost:8080` to see all available endpoints

Next try it out:

Using curl

```console
$ curl -I http://localhost:8080/status/418
HTTP/1.1 418 I'm a teapot
Access-Control-Allow-Credentials: true
Access-Control-Allow-Origin: *
Content-Type: text/plain; charset=utf-8
X-More-Info: http://tools.ietf.org/html/rfc2324
Date: Sat, 30 Mar 2024 15:59:44 GMT
```

Using [httpie](https://github.com/httpie/cli)

```console
$ http http://localhost:8080/get?foo=bar
HTTP/1.1 200 OK
Access-Control-Allow-Credentials: true
Access-Control-Allow-Origin: *
Content-Length: 392
Content-Type: application/json; charset=utf-8
Date: Sat, 30 Mar 2024 15:58:45 GMT

{
    "args": {
        "foo": [
            "bar"
        ]
    },
    "headers": {
        "Accept": [
            "*/*"
        ],
        "Accept-Encoding": [
            "gzip, deflate"
        ],
        "Connection": [
            "keep-alive"
        ],
        "Host": [
            "localhost:8080"
        ],
        "User-Agent": [
            "HTTPie/3.2.2"
        ]
    },
    "method": "GET",
    "origin": "10.0.2.2:55852",
    "url": "http://localhost:8080/get?foo=bar"
}
```

## Learn More

- [How to run unikernels locally](https://unikraft.org/docs/cli/running)
- [How to build `Dockerfile` root filesystems with BuildKit](https://unikraft.org/guides/building-dockerfile-images-with-buildkit)
