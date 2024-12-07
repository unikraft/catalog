DIRS = barrier dir open socket stat sysconf

.PHONY: dirs $(DIRS) clean clean-dirs

dirs: $(DIRS)

clean: clean-dirs

$(DIRS):
	$(MAKE) -C $@

clean-dirs:
	@for dir in $(DIRS); do \
		$(MAKE) clean -C $$dir; \
	done
