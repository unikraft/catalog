from prometheus_client import Counter, generate_latest, CONTENT_TYPE_LATEST
from flask import Flask, Response

app = Flask(__name__)

hello_counter = Counter("hello_requests_total", "Total number of hellos served")

@app.route("/hello")
def hello():
    hello_counter.inc()
    return "Hello, Prometheus!\n"

@app.route("/metrics")
def metrics():
    data = generate_latest()
    return Response(data, mimetype=CONTENT_TYPE_LATEST)

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
