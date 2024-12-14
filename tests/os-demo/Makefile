DIRS = access-permissions address-space address-space-threads allocation \
		allocation-granularity buffered-system-io c-file-ops channels \
		creation-time ctxt-switch deadlock demand-paging dirent exec-addr \
		exec-vars executor exploit fdtsize fopen-perm fork-faults \
		fork-file-pointer global-static-local granularity hidden \
		indefinite-wait ioctl lang libc-syscall list-excl lock \
		no-libc open-dup orphan-zombie pipe pipe-exec pmap reentrant \
		ring-buffer run-shellcode save-fd server setuid shared-data \
		shellcode-samples socket-ssp sparse-file spinlock-mutex \
		stack-access stack-smash static-dynamic stdout-stderr \
		sum-threads syscall-nolibc-asm system-memory tocttou \
		truncate yield \

# syscall-libc-call-asm buffer-overflow

.PHONY: dirs $(DIRS) clean clean-dirs

dirs: $(DIRS)

clean: clean-dirs

$(DIRS):
	$(MAKE) -C $@

clean-dirs:
	@for dir in $(DIRS); do \
		$(MAKE) clean -C $$dir; \
	done
