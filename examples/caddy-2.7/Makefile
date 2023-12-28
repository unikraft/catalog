IMAGE_NAME = unikraft-caddy

include ../../utils/bincompat/docker.Makefile

export: clean create cleanfs
	mkdir rootfs
	docker export $(CONTAINER_NAME) | tar -x -C rootfs
	cp hosts rootfs/etc/hosts
