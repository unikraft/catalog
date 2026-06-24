"""Simple HTTP GET test for Hyperlight networking.

Uses raw sockets to avoid DNS dependency for initial testing.
Connects to example.com and issues a GET /.
"""
import socket
import sys

HOST = "172.66.147.243"
PORT = 80
PATH = "/"

print(f"Connecting to {HOST}:{PORT}...")
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((HOST, PORT))
print("Connected!")

request = f"GET {PATH} HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n"
sock.sendall(request.encode())
print("Request sent, waiting for response...")

response = b""
while True:
    chunk = sock.recv(4096)
    if not chunk:
        break
    response += chunk

sock.close()

text = response.decode("utf-8", errors="replace")
lines = text.split("\r\n")
print(f"Status: {lines[0]}")
print(f"Body length: {len(text)} bytes")

if "200 OK" in lines[0]:
    print("SUCCESS: HTTP GET worked!")
else:
    print(f"UNEXPECTED: {lines[0]}")
    sys.exit(1)
