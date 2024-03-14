use tiny_http::{Server, Response};

fn main() -> std::io::Result<()> {
    let server = Server::http("0.0.0.0:8080").unwrap();
    let port = server.server_addr().to_ip().unwrap().port();
    println!("Now listening on port {port}");

    for request in server.incoming_requests() {
        println!("Received {request:?}");

        let response = Response::from_string("Hello, world!\r\n");
        request.respond(response)?;
    }

    Ok(())
}
