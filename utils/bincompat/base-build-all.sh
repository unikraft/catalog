#!/bin/sh

# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2023, Unikraft GmbH and The Unikraft Authors.
#
# Generate strace and debug Kraftfiles and build all kernel images
# for app compat:
#   - qemu-x86_64
#   - fc-x86_64
#   - qemu-x86_64-strace
#   - fc-x86_64-strace
#   - qemu-x86_64-debug
#   - fc-x86_64-debug
#
# This script is to be run from the `library/base/` directory.
# Kernel image files are generated in the `$KERNELDIR` directory.

# Generate Kraftfile for strace-enabled build.
tac Kraftfile | sed '/^\([ \t]\+\)\(CONFIG_.*\)$/ {s/^\([ \t]\+\)\(.*\)$/\1CONFIG_LIBSYSCALL_SHIM_STRACE: '\'y\''\n\1\2/; :loop; n; b loop}' | tac > Kraftfile.strace

# Generate Kraftfile for all debug-enabled build.
tac Kraftfile | sed '/^\([ \t]\+\)\(CONFIG_.*\)$/ {s/^\([ \t]\+\)\(.*\)$/\1CONFIG_LIBSYSCALL_SHIM_STRACE: '\'y\''\n\1CONFIG_LIBSYSCALL_SHIM_DEBUG: '\'y\''\n\1CONFIG_LIBUKDEBUG_PRINTK_INFO: '\'y\''\n\1CONFIG_LIBUKDEBUG_PRINTD: '\'y\''\n\1\2/; :loop; n; b loop}' | tac > Kraftfile.debug

KERNELDIR="../../kernels"

test -d "$KERNELDIR" || mkdir "$KERNELDIR"

rm -f .config*
rm -fr .unikraft

kraft build --no-cache --plat qemu --arch x86_64
cp .unikraft/build/base_qemu-x86_64 "$KERNELDIR"/base_qemu-x86_64

kraft build --no-cache --plat fc --arch x86_64
cp .unikraft/build/base_fc-x86_64 "$KERNELDIR"/base_fc-x86_64

kraft build -K Kraftfile.strace --no-cache --plat qemu --arch x86_64
cp .unikraft/build/base_qemu-x86_64 "$KERNELDIR"/base_qemu-x86_64-strace

kraft build -K Kraftfile.strace --no-cache --plat fc --arch x86_64
cp .unikraft/build/base_fc-x86_64 "$KERNELDIR"/base_fc-x86_64-strace

kraft build -K Kraftfile.debug --no-cache --plat qemu --arch x86_64
cp .unikraft/build/base_qemu-x86_64 "$KERNELDIR"/base_qemu-x86_64-debug

kraft build -K Kraftfile.debug --no-cache --plat fc --arch x86_64
cp .unikraft/build/base_fc-x86_64 "$KERNELDIR"/base_fc-x86_64-debug
