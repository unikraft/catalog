"""Simple TCP echo server for testing host-proxied networking.

Binds to 0.0.0.0:8080 and echoes back whatever a client sends,
prefixed with "ECHO: ". Exits after the first client disconnects.
"""
import socket

HOST = "0.0.0.0"
PORT = 8080

srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
srv.bind((HOST, PORT))
srv.listen(1)
print(f"Listening on {HOST}:{PORT}...")

conn, addr = srv.accept()
print(f"Connection from {addr}")

while True:
    data = conn.recv(1024)
    if not data:
        break
    reply = b"ECHO: " + data
    conn.sendall(reply)
    print(f"Echoed {len(data)} bytes")

conn.close()
srv.close()
print("Server done.")
