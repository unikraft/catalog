// https://www.logicbig.com/tutorials/core-java-tutorial/http-server/http-server-basic.html

import com.sun.net.httpserver.HttpContext;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class SimpleHttpServer {
    private static final int listenPort = 8080;

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(listenPort), 0);
        HttpContext context = server.createContext("/");
        context.setHandler(SimpleHttpServer::handleRequest);
        System.out.println("Waiting for HTTP connections on port " + listenPort + " ...");
        server.start();
    }

    private static void handleRequest(HttpExchange exchange) throws IOException {
        String response = "Hello, World!\n";
        exchange.sendResponseHeaders(200, response.getBytes().length); // response code and length
        OutputStream os = exchange.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }

}
