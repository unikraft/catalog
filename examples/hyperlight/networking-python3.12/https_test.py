import urllib.request
import sys

print("Testing HTTPS (TLS) through proxied sockets...")
try:
    with urllib.request.urlopen("https://api.github.com", timeout=10) as r:
         print(f"Status: {r.status}")
    print("SUCCESS: HTTPS works!")
except Exception as e:
    print(f"FAILED: {e}")
    sys.exit(1)
