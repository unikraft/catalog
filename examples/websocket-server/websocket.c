#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

typedef struct {
    uint32_t state[5];
    uint32_t count[2];
    unsigned char buffer[64];
} SHA1_CTX;

void SHA1Transform(uint32_t state[5], const unsigned char buffer[64]);
void SHA1Init(SHA1_CTX* context);
void SHA1Update(SHA1_CTX* context, const unsigned char* data, uint32_t len);
void SHA1Final(unsigned char digest[20], SHA1_CTX* context);

/* Base64 implementation */
static const char b64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void base64_encode(const unsigned char *src, size_t len, char *dst) {
    size_t i = 0, j = 0;
    for (; i < len; i += 3) {
        uint32_t v = src[i] << 16;
        if (i+1 < len) v |= src[i+1] << 8;
        if (i+2 < len) v |= src[i+2];
        
        dst[j++] = b64_table[(v >> 18) & 0x3F];
        dst[j++] = b64_table[(v >> 12) & 0x3F];
        dst[j++] = (i+1 < len) ? b64_table[(v >> 6) & 0x3F] : '=';
        dst[j++] = (i+2 < len) ? b64_table[v & 0x3F] : '=';
    }
    dst[j] = '\0';
}

char *generate_accept_key(const char *client_key) {
    static char accept_key[64];
    unsigned char sha_digest[20];
    SHA1_CTX ctx;
    char combined[128];
    
    snprintf(combined, sizeof(combined), "%s258EAFA5-E914-47DA-95CA-C5AB0DC85B11", client_key);
    
    SHA1Init(&ctx);
    SHA1Update(&ctx, (unsigned char *)combined, strlen(combined));
    SHA1Final(sha_digest, &ctx);
    
    base64_encode(sha_digest, sizeof(sha_digest), accept_key);
    return accept_key;
}

int main(void) {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    
    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Set socket option to reuse address
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    // Configure address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    
    printf("WebSocket server running on port %d\n", PORT);
    
    while(1) {
        printf("Waiting for new connection...\n");
        
        // Accept connection
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, 
                                (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }
        
        printf("Connection established\n");
        
        // Read request
        int bytes_read = read(client_fd, buffer, BUFFER_SIZE);
        printf("Received: %s\n", buffer);
        
        // Extract the Sec-WebSocket-Key
        char *key_start = strstr(buffer, "Sec-WebSocket-Key: ");
        char *key = NULL;
        
        if (key_start) {
            key_start += 19; 
            char *key_end = strstr(key_start, "\r\n");
            if (key_end) {
                int key_len = key_end - key_start;
                key = malloc(key_len + 1);
                strncpy(key, key_start, key_len);
                key[key_len] = '\0';
                printf("Found WebSocket key: %s\n", key);
            }
        }
        
        // Check if this is a WebSocket upgrade request
        if (strstr(buffer, "Upgrade: websocket") != NULL && key) {
            char *accept_key = generate_accept_key(key);
            
            // Send handshake response
            char response[256];
            snprintf(response, sizeof(response),
                   "HTTP/1.1 101 Switching Protocols\r\n"
                   "Upgrade: websocket\r\n"
                   "Connection: Upgrade\r\n"
                   "Sec-WebSocket-Accept: %s\r\n"
                   "\r\n", accept_key);
            
            send(client_fd, response, strlen(response), 0);
            printf("WebSocket handshake response sent\n");
            
            // Main WebSocket communication loop
            while(1) {
                memset(buffer, 0, BUFFER_SIZE);
                bytes_read = read(client_fd, buffer, BUFFER_SIZE);
                
                if (bytes_read <= 0) {
                    printf("Client disconnected\n");
                    break;
                }
                
                // Print raw bytes received for debugging
                printf("Received %d bytes: ", bytes_read);
                for (int i = 0; i < bytes_read && i < 16; i++) {
                    printf("%02x ", (unsigned char)buffer[i]);
                }
                printf("\n");
                
                // Simple response with "Hello" (WebSocket text frame)
                unsigned char response[10];
                response[0] = 0x81;  // FIN bit + Text frame
                response[1] = 0x05;  // Payload length (5 bytes for "Hello")
                memcpy(response+2, "Hello", 5);
                
                send(client_fd, response, 7, 0);
                printf("Sent response message\n");
            }
            
            free(key);
        } else {
            // Not a WebSocket request
            char *response = "HTTP/1.1 400 Bad Request\r\n\r\nWebSocket only\r\n";
            send(client_fd, response, strlen(response), 0);
        }
        
        close(client_fd);
    }
    
    close(server_fd);
    return 0;
}