#!/usr/bin/env python3
"""Query the chronyd unikernel: test.py [host] [port] (default 127.0.0.1 1123).

Exits non-zero unless chronyd answers and has synchronized upstream.
"""

import socket
import struct
import sys
import time

REF_TIME_1970 = 2208988800  # NTP epoch (1900) -> Unix epoch (1970)


def RequestTimefromNtp(addr="127.0.0.1", port=1123):
    client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    client.settimeout(5)
    client.sendto(b"\x1b" + 47 * b"\0", (addr, port))
    data, _ = client.recvfrom(48)
    t = struct.unpack("!12I", data)[10] - REF_TIME_1970
    stratum = data[1]
    refid = ".".join(str(b) for b in data[12:16])  # selected upstream
    return stratum, refid, time.ctime(t)


if __name__ == "__main__":
    host = sys.argv[1] if len(sys.argv) > 1 else "127.0.0.1"
    port = int(sys.argv[2]) if len(sys.argv) > 2 else 1123
    try:
        stratum, refid, served = RequestTimefromNtp(host, port)
    except TimeoutError:
        sys.exit(f"no reply from {host}:{port}")

    print("stratum:", stratum)
    print("refid:  ", refid)
    print("time:   ", served)

    if stratum == 0:
        sys.exit("answering but not synchronized yet, retry shortly")
