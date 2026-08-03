use std::io::{Read, Write};
use std::net::{TcpListener, TcpStream};

fn handle_client(mut stream: TcpStream) {
    let mut buf = [0u8; 2048];
    if let Ok(n) = stream.read(&mut buf) {
        if n > 0 {
            let req_str = String::from_utf8_lossy(&buf[..n]);
            if req_str.starts_with("GET") {
                let response = b"HTTP/1.1 200 OK\r\n\
                                Content-Type: text/html; charset=utf-8\r\n\
                                Content-Length: 56\r\n\
                                Connection: close\r\n\r\n\
                                <html><body><h1>Hello from Rust on Hyperlight!</h1></body></html>\n";
                let _ = stream.write_all(response);
            } else {
                let not_found = b"HTTP/1.1 404 Not Found\r\n\
                                  Content-Type: text/plain\r\n\
                                  Content-Length: 10\r\n\
                                  Connection: close\r\n\r\n\
                                  Not Found\n";
                let _ = stream.write_all(not_found);
            }
        }
    }
}

fn main() {
    let listener = match TcpListener::bind("0.0.0.0:8080") {
        Ok(l) => l,
        Err(e) => {
            eprintln!("Failed to bind socket: {}", e);
            std::process::exit(1);
        }
    };

    println!("Serving on http://0.0.0.0:8080...");

    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                handle_client(stream);
            }
            Err(e) => {
                eprintln!("Accept failed: {}", e);
            }
        }
    }
}
