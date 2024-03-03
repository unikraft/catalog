"""
Simple HTTP server

Serves a simple "Hello, World!" string as response to basic HTTP GET requests.
"""

import argparse
from http.server import HTTPServer, BaseHTTPRequestHandler

class MyServer(BaseHTTPRequestHandler):
    """HTTP Server class"""
    def do_GET(self):
        """Reply with a simple message to HTTP GET requests."""
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write(bytes("Hello, World!\n", "utf-8"))

def parse_args():
    """Parse command line arguments, if provided."""
    parser = argparse.ArgumentParser()
    parser.add_argument("--host", type=str, default="0.0.0.0")
    parser.add_argument("--port", type=int, default=8080)
    return parser.parse_args()

def main(args):
    """Start HTTP server and wait for connections."""
    server = HTTPServer((args.host, args.port), MyServer)

    print(f"starting server at {args.host}:{args.port}")

    try:
        server.serve_forever()

    except KeyboardInterrupt:
        pass

    print("server stopped")

if __name__ == "__main__":
    main(parse_args())
