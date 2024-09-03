## Compose sample application

### NGINX proxy with Go backend

This example was derived from the [nginx-golang docker/awesome-compose example](https://github.com/docker/awesome-compose/tree/master/nginx-golang).

Project structure:

```bash
.
├── backend
│   ├── Kraftfile
│   ├── Dockerfile
│   └── main.go
├── compose.yaml
├── proxy
│   └── nginx.conf
└── README.md
```

[`compose.yaml`](compose.yaml)

```yml
services:
  proxy:
    image: nginx:1.25
    volumes:
      - ./proxy:/etc/nginx
    ports:
      - 8080:80
    depends_on:
      - backend
    networks:
      internal:

  backend:
    build:
      context: backend
    networks:
      internal:
        ipv4_address: 172.23.0.2

networks:
  internal:
    ipam:
      config:
        - subnet: 172.23.0.1/16
```

The compose file defines an application with two services `proxy` and `backend`.
When deploying the application, kraft compose maps port 80 of the frontend service VM to port 8080 of the host as specified in the file.
Make sure port 8080 on the host is not already in use.

## Deploy with kraft compose

```bash
$ kraft compose up -d
creating network nginx-golang_internal...
nginx-golang_internal
 i  building service backend...
...
nginx-golang-backend
nginx-golang-proxy
```

## Expected result

Listing VMs must show two VMs running and the port mapping as below:

```bash
$ kraft compose ps
NAME                  KERNEL                          ARGS            CREATED         STATUS   MEM  PORTS                 PLAT
nginx-golang-backend  oci://unikraft.org/base:latest  /server         23 seconds ago  running  64M                        qemu/x86_64
nginx-golang-proxy    oci://nginx:1.25                /usr/bin/nginx  22 seconds ago  running  64M  0.0.0.0:8080->80/tcp  qemu/x86_64
```

After the application starts, navigate to `http://localhost:8080` in your web browser or run:

```bash
$ curl localhost:8080
 .--------------------.
( Hello from Unikraft! )
 '--------------------'
         \\
          \\
             _
           c'o'o  .--.
           (| |)_/
```

Stop and remove the VMs

```bash
kraft compose down
```
