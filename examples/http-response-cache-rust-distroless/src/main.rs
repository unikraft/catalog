use std::collections::HashMap;
use std::io::{Read, Write};
use std::net::{TcpListener, TcpStream};
use std::sync::{Arc, Mutex};

fn handle_client(mut stream: TcpStream, cache: Arc<Mutex<HashMap<String, String>>>) {
    let mut buffer = [0; 4096];

    let Ok(size) = stream.read(&mut buffer) else {
        return;
    };

    let request = String::from_utf8_lossy(&buffer[..size]);

    let Some(request_line) = request.lines().next() else {
        return;
    };

    let mut parts = request_line.split_whitespace();

    let Some(method) = parts.next() else {
        return;
    };

    let Some(path) = parts.next() else {
        return;
    };

    if method != "GET" {
        let response =
            "HTTP/1.1 405 Method Not Allowed\r\nContent-Length: 18\r\n\r\nMethod Not Allowed";
        let _ = stream.write_all(response.as_bytes());
        return;
    }

    let mut cache = cache.lock().unwrap();

    let body = if let Some(value) = cache.get(path) {
        format!("CACHE HIT: {value}")
    } else {
        let value = format!("Generated response for {path}");
        cache.insert(path.to_string(), value.clone());
        format!("CACHE MISS: {value}")
    };

    let response = format!(
        "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: {}\r\n\r\n{}",
        body.len(),
        body
    );

    let _ = stream.write_all(response.as_bytes());
}

fn main() {
    let listener = TcpListener::bind("0.0.0.0:8080").expect("failed to bind port 8080");

    let cache = Arc::new(Mutex::new(HashMap::new()));

    println!("HTTP response cache listening on port 8080");

    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                let cache = Arc::clone(&cache);

                std::thread::spawn(move || {
                    handle_client(stream, cache);
                });
            }
            Err(error) => {
                eprintln!("connection error: {error}");
            }
        }
    }
}