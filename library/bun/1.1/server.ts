const port = process.env.PORT || 3000;

console.log(
  `Launching Bun HTTP server on port: ${port}, url: http://0.0.0.0:${port} 🚀`
);

Bun.serve({
  port: port,
  fetch(_request) {
    return new Response("Hello, World!");
  },
});
