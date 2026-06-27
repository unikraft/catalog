#!/usr/bin/env python3
"""Transparent POSIX filesystem access on Hyperlight, from Python.

lib/hostfs auto-mounts the host directory (passed via
`hyperlight-unikraft --mount <dir>`) at /host, and forwards every
vnode op to the host's FsSandbox tool handlers. This program uses
standard Python stdlib — open/read/write/os.mkdir/os.stat — against
/host; no hyperlight SDK, no JSON, no /dev/hcall.

Note: os.listdir() and glob() rely on opendir/readdir, which don't
work yet (see the hostfs README). Enumerate paths you know about
or stat them individually.
"""
import os

print("hostfs-posix-py: unmodified Python stdlib against the sandboxed host mount")

# 1. Write a file.
msg = ("Hello from Unikraft via transparent POSIX (Python)!\n"
       "Just open() and write() — no SDK imports.\n")
with open("/host/greeting.txt", "w") as f:
    n = f.write(msg)
    print(f"wrote /host/greeting.txt ({n} chars)")

# 2. Read it back.
with open("/host/greeting.txt", "r") as f:
    got = f.read()
print(f"read /host/greeting.txt ({len(got)} chars):\n---\n{got}---")

# 3. Create a subdirectory and append to a file.
try:
    os.mkdir("/host/logs")
except FileExistsError:
    pass
with open("/host/logs/app.log", "a") as f:
    f.write("line 1\n")
    f.write("line 2\n")
print("appended to /host/logs/app.log")

# 4. stat.
st = os.stat("/host/greeting.txt")
print(f"stat /host/greeting.txt: size={st.st_size}")

# 5. Truncate.
with open("/host/greeting.txt", "r+") as f:
    f.truncate(5)
st = os.stat("/host/greeting.txt")
print(f"after truncate(5): size={st.st_size}")
with open("/host/greeting.txt", "r") as f:
    print(f"content: {f.read()!r}")

print("done.")
