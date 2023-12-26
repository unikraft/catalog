# https://dev.to/leandronsp/web-basics-a-simple-http-server-in-ruby-2jj4

require 'socket'

socket = TCPServer.new(8080)

loop do
  client = socket.accept

  request = client.gets

  response = "HTTP/1.1 200 OK\r\n" \
    "Content-type: text/html\r\n" \
    "Connection: close\r\n" \
    "\r\n" \
    "Hello, World!"
  client.puts(response)

  client.close
end
