## Compose sample application

## Node.js application with Nginx proxy and Redis database

This example was derived from the [nginx-nodejs-redis docker/awesome-compose example](https://github.com/docker/awesome-compose/tree/master/nginx-nodejs-redis).

Project structure:

```bash
.
├── README.md
├── compose.yaml
├── nginx
│   └── nginx.conf
└── web
    ├── Kraftfile
    ├── Dockerfile
    ├── package.json
    └── server.js

2 directories, 7 files


```

[_compose.yaml_](compose.yaml)

```yaml
services:
  redis:
    image: redis:7.2
    ports:
      - '6379:6379'
    networks:
      internal:
        ipv4_address: 172.23.0.2
    mem_reservation: 512M

  web1:
    build: ./web
    hostname: web1
    networks:
      internal:
        ipv4_address: 172.23.0.3
    mem_reservation: 512M
    depends_on:
      - redis

  web2:
    build: ./web
    hostname: web2
    networks:
      internal:
        ipv4_address: 172.23.0.4
    mem_reservation: 512M
    depends_on:
      - redis

  nginx:
    image: nginx:1.25
    ports:
    - '8080:80'
    volumes:
      - ./nginx:/etc/nginx
    depends_on:
    - web1
    - web2
    networks:
      internal:

networks:
  internal:
    ipam:
      config:
        - subnet: 172.23.0.1/16
```

The compose file defines an application with four services `redis`, `nginx`, `web1` and `web2`.
When deploying the application, docker compose maps port 80 of the nginx service VM to port 8080 of the host as specified in the file.

> **_INFO_**
> Redis runs on port 6379 by default.
> Make sure port 6379 on the host is not being used by another VM, otherwise the port should be changed.

## Deploy with kraft compose

```bash
$ sudo kraft compose up -d
nginx-nodejs-redis-redis
nginx-nodejs-redis-web1
nginx-nodejs-redis-web2
nginx-nodejs-redis-nginx
```

## Expected result

Listing VMs must show four VMs running and the port mapping as below:

```bash
$ sudo kraft compose ps
NAME                      KERNEL                      ARGS                                         CREATED        STATUS   MEM   PORTS                   PLAT
nginx-nodejs-redis-nginx  oci://nginx:1.25            /usr/bin/nginx                               2 minutes ago  running  64M   0.0.0.0:8080->80/tcp    qemu/x86_64
nginx-nodejs-redis-redis  oci://redis:7.2             /usr/bin/redis-server /etc/redis/redis.conf  2 minutes ago  running  512M  0.0.0.0:6379->6379/tcp  qemu/x86_64
nginx-nodejs-redis-web1   oci://unikraft.org/node:21  /usr/bin/node /usr/src/server.js             2 minutes ago  running  512M                          qemu/x86_64
nginx-nodejs-redis-web2   oci://unikraft.org/node:21  /usr/bin/node /usr/src/server.js             2 minutes ago  running  512M                          qemu/x86_64
```

## Testing the app

After the application starts, navigate to `http://localhost:8080` in your web browser or run:

```bash
$ curl localhost:8080
web1: Total number of visits is: 1
```

```bash
$ curl localhost:8080
web2: Total number of visits is: 2
```

```bash
$ curl localhost:8080
web1: Total number of visits is: 3
```

## Stop and remove the VMs

```bash
sudo kraft compose down
```
