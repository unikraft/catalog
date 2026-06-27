"""CI smoke test that `--port` allows bind+listen.

This is a run-to-completion test: it binds, listens, then exits. If bind+listen
succeed (instead of raising OSError), the `--port` allowlist is working.
"""
import socket

HOST = "0.0.0.0"
PORT = 8080

srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
srv.bind((HOST, PORT))
srv.listen(1)
srv.close()
print("SUCCESS: bind+listen on port 8080 allowed")
