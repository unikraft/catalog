#!/usr/bin/env python3
"""Strip PT_INTERP from a static PIE binary.

Go's internal linker adds /lib64/ld-linux-x86-64.so.2 as PT_INTERP for PIE
binaries on Linux, but a CGO_ENABLED=0 binary is fully self-contained and
does not need a dynamic linker. Patch PT_INTERP -> PT_NULL so elfloaders
that reject missing interpreters will load the binary directly.
"""
import struct
import sys

path = sys.argv[1]
with open(path, "rb") as f:
    data = bytearray(f.read())

e_phoff,     = struct.unpack_from("<Q", data, 32)
e_phentsize, = struct.unpack_from("<H", data, 54)
e_phnum,     = struct.unpack_from("<H", data, 56)

for i in range(e_phnum):
    off = e_phoff + i * e_phentsize
    p_type, = struct.unpack_from("<I", data, off)
    if p_type == 3:  # PT_INTERP
        struct.pack_into("<I", data, off, 0)  # PT_NULL
        print(f"Patched PT_INTERP -> PT_NULL at program header index {i}")

with open(path, "wb") as f:
    f.write(data)
