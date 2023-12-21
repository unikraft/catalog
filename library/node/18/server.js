const http = require('http');

const server = http.createServer((req, resp) => {
  resp.writeHead(200, {
    'Content-Type': 'text/plain'
  });

  resp.write('Hello, world!\n');

  resp.end();
})

server.listen(8080, "0.0.0.0", () => {
  console.log(`Listening on :8080...`);
});
