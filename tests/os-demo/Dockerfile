FROM gcc:12.4.0-bookworm AS build

WORKDIR /src

COPY ./access-permissions /src/access-permissions
COPY ./address-space /src/address-space
COPY ./address-space-threads /src/address-space-threads
COPY ./allocation /src/allocation
COPY ./allocation-granularity /src/allocation-granularity
# COPY ./buffer-overflow /src/buffer-overflow
COPY ./buffered-system-io /src/buffered-system-io
COPY ./c-file-ops /src/c-file-ops
COPY ./channels /src/channels
COPY ./creation-time /src/creation-time
COPY ./ctxt-switch /src/ctxt-switch
COPY ./deadlock /src/deadlock
COPY ./demand-paging /src/demand-paging
COPY ./dirent /src/dirent
COPY ./exec-addr /src/exec-addr
COPY ./exec-vars /src/exec-vars
COPY ./executor /src/executor
COPY ./exploit /src/exploit
COPY ./fdtsize /src/fdtsize
COPY ./fopen-perm /src/fopen-perm
COPY ./fork-faults /src/fork-faults
COPY ./fork-file-pointer /src/fork-file-pointer
COPY ./global-static-local /src/global-static-local
COPY ./granularity /src/granularity
COPY ./hidden /src/hidden
COPY ./indefinite-wait /src/indefinite-wait
COPY ./ioctl /src/ioctl
COPY ./lang /src/lang
COPY ./libc-syscall /src/libc-syscall
COPY ./list-excl /src/list-excl
COPY ./lock /src/lock
COPY ./no-libc /src/no-libc
COPY ./open-dup /src/open-dup
COPY ./orphan-zombie /src/orphan-zombie
COPY ./pipe /src/pipe
COPY ./pipe-exec /src/pipe-exec
COPY ./pmap /src/pmap
COPY ./reentrant /src/reentrant
COPY ./ring-buffer /src/ring-buffer
COPY ./run-shellcode /src/run-shellcode
COPY ./save-fd /src/save-fd
COPY ./server /src/server
COPY ./setuid /src/setuid
COPY ./shared-data /src/shared-data
COPY ./shellcode-samples /src/shellcode-samples
COPY ./socket-ssp /src/socket-ssp
COPY ./sparse-file /src/sparse-file
COPY ./spinlock-mutex /src/spinlock-mutex
COPY ./stack-access /src/stack-access
COPY ./stack-smash /src/stack-smash
COPY ./static-dynamic /src/static-dynamic
COPY ./stdout-stderr /src/stdout-stderr
COPY ./sum-threads /src/sum-threads
# COPY ./syscall-libc-call-asm /src/syscall-libc-call-asm
COPY ./syscall-nolibc-asm /src/syscall-nolibc-asm
COPY ./system-memory /src/system-memory
COPY ./tocttou /src/tocttou
COPY ./truncate /src/truncate
COPY ./yield /src/yield
COPY ./utils /src/utils
COPY ./Makefile /src

RUN set -xe; \
	apt-get -yqq update; \
	apt-get -yqq install \
		gdc \
		gcc-multilib \
		libc6-dev-i386 \
		default-jdk \
		default-jre \
		python3 \
		nasm; \
	dpkg --add-architecture i386; \
	apt-get -yqq update; \
	apt-get -yqq install libc6:i386 libc6-dev:i386 lib32gcc-12-dev \
	;

RUN make

FROM scratch

# Binaries
COPY --from=build /src/access-permissions/access-permissions /access-permissions
COPY --from=build /src/address-space/address-space /address-space
COPY --from=build /src/address-space-threads/address-space-threads /address-space-threads
COPY --from=build /src/allocation/allocation /allocation
COPY --from=build /src/allocation-granularity/allocation-granularity /allocation-granularity
# COPY --from=build /src/buffer-overflow/buffer-overflow /buffer-overflow
COPY --from=build /src/buffered-system-io/buffered /buffered
COPY --from=build /src/buffered-system-io/system /system
COPY --from=build /src/c-file-ops/c-file-ops /c-file-ops
COPY --from=build /src/channels/channels /channels
COPY --from=build /src/creation-time/process-overhead /process-overhead
COPY --from=build /src/creation-time/thread-overhead /thread-overhead
COPY --from=build /src/ctxt-switch/cpu /cpu
COPY --from=build /src/ctxt-switch/io /io
COPY --from=build /src/deadlock/deadlock /deadlock
COPY --from=build /src/demand-paging/demand-paging /demand-paging
COPY --from=build /src/dirent/dirent /dirent
COPY --from=build /src/exec-addr/exec-addr /exec-addr
COPY --from=build /src/exec-vars/exec-vars /exec-vars
COPY --from=build /src/executor/executor_ansi /executor_ansi
COPY --from=build /src/executor/executor_spawn /executor_spawn
COPY --from=build /src/executor/executor_system /executor_system
COPY --from=build /src/executor/printer /printer
COPY --from=build /src/exploit/exploit /exploit
COPY --from=build /src/fdtsize/fdtsize /fdtsize
COPY --from=build /src/fopen-perm/fopen-perm /fopen-perm
COPY --from=build /src/fork-faults/fork-faults /fork-faults
COPY --from=build /src/fork-file-pointer/fork-file-pointer /fork-file-pointer
COPY --from=build /src/global-static-local/global-static-local /global-static-local
COPY --from=build /src/granularity/granularity-fine /granularity-fine
COPY --from=build /src/granularity/granularity-coarse /granularity-coarse
COPY --from=build /src/hidden/hidden /hidden
COPY --from=build /src/indefinite-wait/indefinite-wait /indefinite-wait
COPY --from=build /src/ioctl/hwaddr-ioctl /hwaddr-ioctl
COPY --from=build /src/ioctl/cdrom-ioctl /cdrom-ioctl
COPY --from=build /src/lang/MultithreadingTest.class /MultithreadingTest.class
COPY --from=build /src/libc-syscall/caller /caller
COPY --from=build /src/list-excl/thread-list-app /thread-list-app
COPY --from=build /src/list-excl/thread-list-app-mutex /thread-list-app-mutex
COPY --from=build /src/lock/lock /lock
COPY --from=build /src/lock/lock_atomic /lock_atomic
COPY --from=build /src/lock/lock_spin /lock_spin
COPY --from=build /src/no-libc/hello-gas /hello-gas
COPY --from=build /src/no-libc/hello-nasm /hello-nasm
COPY --from=build /src/open-dup/dup /dup
COPY --from=build /src/open-dup/open /open
COPY --from=build /src/orphan-zombie/orphan /orphan
COPY --from=build /src/orphan-zombie/zombie /zombie
COPY --from=build /src/pipe/pipe /pipe
COPY --from=build /src/pipe-exec/executor /executor
COPY --from=build /src/pipe-exec/reader /reader
COPY --from=build /src/pipe-exec/writer /writer
COPY --from=build /src/pmap/pmap /pmap
COPY --from=build /src/reentrant/reentrant /reentrant
COPY --from=build /src/reentrant/reentrant-ok /reentrant-ok
COPY --from=build /src/ring-buffer/producer_consumer /producer_consumer
COPY --from=build /src/run-shellcode/run-shellcode /run-shellcode
COPY --from=build /src/save-fd/save-fd /save-fd
COPY --from=build /src/server/server /server
COPY --from=build /src/setuid/setuid /setuid
COPY --from=build /src/shared-data/process /process
COPY --from=build /src/shellcode-samples/shellcode-samples /shellcode-samples
COPY --from=build /src/socket-ssp/socket-ssp /socket-ssp
COPY --from=build /src/sparse-file/sparse-file /sparse-file
COPY --from=build /src/spinlock-mutex/mutex /mutex
COPY --from=build /src/spinlock-mutex/spinlock /spinlock
COPY --from=build /src/stack-access/stack-access /stack-access
COPY --from=build /src/stack-smash/stack-smash-protector /stack-smash-protector
COPY --from=build /src/stack-smash/stack-smash-no-protector /stack-smash-no-protector
COPY --from=build /src/static-dynamic/hello-static /hello-static
COPY --from=build /src/static-dynamic/hello-dynamic /hello-dynamic
COPY --from=build /src/stdout-stderr/stdout-stderr /stdout-stderr
COPY --from=build /src/sum-threads/sum-threads /sum-threads
COPY --from=build /src/sum-threads/sum-threads-atomic /sum-threads-atomic
# COPY --from=build /src/syscall-libc-call-asm/syscall-libc-call /syscall-libc-call
COPY --from=build /src/syscall-nolibc-asm/syscall-nolibc /syscall-nolibc
COPY --from=build /src/system-memory/system-memory /system-memory
COPY --from=build /src/tocttou/tocttou /tocttou
COPY --from=build /src/truncate/truncate /truncate
COPY --from=build /src/yield/yield /yield

# Text files
COPY --from=build /src/dirent/rootfs /rootfs/
COPY --from=build /src/fdtsize/file /file
COPY --from=build /src/fopen-perm/aaa /aaa
COPY --from=build /src/libc-syscall/a.txt /a.txt
COPY --from=build /src/libc-syscall/b.txt /b.txt
COPY --from=build /src/open-dup/Makefile /Makefile

# Libraries
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/
