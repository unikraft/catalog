use std::net::SocketAddr;
use tokio::net::TcpListener;
use tokio::io::{AsyncReadExt, AsyncWriteExt};

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let addr = SocketAddr::from(([0, 0, 0, 0], 8080));
    let listener = TcpListener::bind(&addr).await?;

    println!("Listening on: http://{}", addr);

    loop {
        let (mut stream, _) = listener.accept().await?;

        tokio::spawn(async move {
            loop {
                let mut buffer = [0; 1024];
                let _ = stream.read(&mut buffer).await;

                let contents = "Hello, World!\r\n";
                let content_length = contents.len();
                let response = format!("HTTP/1.1 200 OK\r\nContent-Length: {content_length}\r\n\r\n{contents}");
                let _ = stream.write_all(response.as_bytes()).await;
            }
        });
    }
}
