#!/usr/bin/env python3

import json
import os
from http import HTTPStatus
from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import urlparse


HOST = "0.0.0.0"
PORT = int(os.environ.get("PORT", "8080"))


class RequestHandler(BaseHTTPRequestHandler):
    server_version = "UnikraftHyperlightHTTP/1.0"

    def do_GET(self):
        if self._path == "/wrk":
            self._send_method_not_allowed(["POST"])
            return

        if self._path != "/":
            self._send_not_found()
            return

        body = (
            "<!doctype html>\n"
            "<html lang=\"en\">\n"
            "<head><meta charset=\"utf-8\"><title>Unikraft Hyperlight</title></head>\n"
            "<body><h1>Hello from Unikraft on Hyperlight</h1></body>\n"
            "</html>\n"
        ).encode("utf-8")
        self._send_response(HTTPStatus.OK, body, "text/html; charset=utf-8")

    def do_POST(self):
        if self._path == "/":
            self._send_method_not_allowed(["GET", "HEAD"])
            return

        if self._path != "/wrk":
            self._send_not_found()
            return

        content_length = self.headers.get("Content-Length")
        try:
            body_length = int(content_length) if content_length else 0
        except ValueError:
            self._send_response(
                HTTPStatus.BAD_REQUEST,
                b'{"error":"invalid content-length"}\n',
                "application/json",
            )
            return

        if body_length > 0:
            self.rfile.read(body_length)

        body = json.dumps({"received_bytes": body_length}).encode("utf-8") + b"\n"
        self._send_response(HTTPStatus.OK, body, "application/json")

    def do_HEAD(self):
        if self._path == "/":
            self._send_response(HTTPStatus.OK, b"", "text/html; charset=utf-8")
            return

        if self._path == "/wrk":
            self._send_method_not_allowed(["POST"])
            return

        self._send_not_found()

    def do_PUT(self):
        self._send_method_not_allowed_for_path()

    def do_DELETE(self):
        self._send_method_not_allowed_for_path()

    def do_PATCH(self):
        self._send_method_not_allowed_for_path()

    def do_OPTIONS(self):
        self._send_method_not_allowed_for_path()

    @property
    def _path(self):
        return urlparse(self.path).path

    def _send_method_not_allowed_for_path(self):
        if self._path == "/":
            self._send_method_not_allowed(["GET", "HEAD"])
            return

        if self._path == "/wrk":
            self._send_method_not_allowed(["POST"])
            return

        self._send_not_found()

    def _send_not_found(self):
        self._send_response(HTTPStatus.NOT_FOUND, b"not found\n", "text/plain")

    def _send_method_not_allowed(self, allowed_methods):
        self.send_response(HTTPStatus.METHOD_NOT_ALLOWED)
        self.send_header("Allow", ", ".join(allowed_methods))
        self.send_header("Content-Length", "0")
        self.end_headers()

    def _send_response(self, status, body, content_type):
        self.send_response(status)
        self.send_header("Content-Type", content_type)
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        if body:
            self.wfile.write(body)


def main():
    with HTTPServer((HOST, PORT), RequestHandler) as server:
        print(f"Serving on http://{HOST}:{PORT}", flush=True)
        server.serve_forever()


if __name__ == "__main__":
    main()
