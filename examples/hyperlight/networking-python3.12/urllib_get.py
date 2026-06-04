"""High-level HTTP GET using urllib (Python stdlib).

Demonstrates that Python's standard urllib.request module works
over the host-proxied socket layer with full DNS resolution.
"""
import urllib.request
import sys

URL = "http://example.com/"

print(f"Fetching {URL} ...")
try:
    with urllib.request.urlopen(URL, timeout=10) as resp:
        body = resp.read().decode("utf-8", errors="replace")
        print(f"Status: {resp.status}")
        print(f"Body length: {len(body)} bytes")
        if "Example Domain" in body:
            print("SUCCESS: urllib GET worked!")
        else:
            print("WARNING: unexpected body content")
except Exception as e:
    print(f"FAILED: {e}")
    sys.exit(1)
