import argparse
from http.server import HTTPServer, BaseHTTPRequestHandler

class MyServer(BaseHTTPRequestHandler):
  def do_GET(self):
    self.send_response(200)
    self.send_header("Content-type", "text/html")
    self.end_headers()
    self.wfile.write(bytes("Hello, World!\n", "utf-8"))

def main(args):
  server = HTTPServer((args.host, args.port), MyServer)

  print("starting server at %s:%s" % (args.host, args.port))

  try:
    server.serve_forever()

  except KeyboardInterrupt:
    pass

  print("server stopped")

def parse_args():
  parser = argparse.ArgumentParser()
  parser.add_argument("--host", type=str, default="0.0.0.0")
  parser.add_argument("--port", type=int, default=8080)
  return parser.parse_args()

if __name__ == "__main__":
  main(parse_args())
