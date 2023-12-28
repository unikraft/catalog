IMAGE_NAME ?= unikraft-base
CONTAINER_NAME ?= $(IMAGE_NAME)
CMD ?= /bin/bash

build:
	docker build -f Dockerfile -t $(IMAGE_NAME) .

run_anon: build
	docker run --rm --interactive --tty $(IMAGE_NAME) $(CMD)

create: build
	-docker container inspect $(CONTAINER_NAME) > /dev/null 2>&1 || docker create --name $(CONTAINER_NAME) --tty $(IMAGE_NAME) $(CMD)

run: create
	-test "$(shell docker container inspect -f '{{{{.State.Running}}}}' $(CONTAINER_NAME) 2> /dev/null)" = "false" || docker exec --interactive --tty $(CONTAINER_NAME) python3 && docker start --interactive $(CONTAINER_NAME)

stop:
	-test "$(shell docker container inspect -f '{{{{.State.Running}}}}' $(CONTAINER_NAME) 2> /dev/null)" = "true" && docker stop $(CONTAINER_NAME)

clean: stop
	-docker container inspect $(CONTAINER_NAME) > /dev/null 2>&1 && docker rm $(CONTAINER_NAME)

export: clean create cleanfs
	mkdir rootfs
	docker export $(CONTAINER_NAME) | tar -x -C rootfs

rootfs: export

rootfs.cpio: rootfs
	cd rootfs/ && find -depth -print | tac | bsdcpio -o --format newc > ../rootfs.cpio

initrd: rootfs.cpio

cleanfs:
	-test -d rootfs && rm -fr rootfs

.PHONY: build build run_anon create run stop clean export initrd cleanfs
