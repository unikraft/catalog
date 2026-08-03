/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2024, Unikraft GmbH and the Unikraft Authors.
 */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define LISTEN_PORT 8080
#define BUFLEN 2048

static const char reply[] = "HTTP/1.1 200 OK\r\n"
			    "Content-Type: text/html; charset=utf-8\r\n"
			    "Content-Length: 55\r\n"
			    "Connection: close\r\n"
			    "\r\n"
			    "<html><body><h1>Hello from Hyperlight!</h1></body></html>\n";

static const char not_found[] = "HTTP/1.1 404 Not Found\r\n"
				"Content-Type: text/plain\r\n"
				"Content-Length: 10\r\n"
				"Connection: close\r\n"
				"\r\n"
				"Not Found\n";

static char recvbuf[BUFLEN];

int main(int argc __attribute__((unused)),
	 char *argv[] __attribute__((unused)))
{
	int rc = 0;
	int srv, client;
	ssize_t n;
	struct sockaddr_in srv_addr;

	srv = socket(AF_INET, SOCK_STREAM, 0);
	if (srv < 0) {
		fprintf(stderr, "Failed to create socket: %d\n", errno);
		return 1;
	}

	int optval = 1;
	setsockopt(srv, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = INADDR_ANY;
	srv_addr.sin_port = htons(LISTEN_PORT);

	rc = bind(srv, (struct sockaddr *) &srv_addr, sizeof(srv_addr));
	if (rc < 0) {
		fprintf(stderr, "Failed to bind socket: %d\n", errno);
		close(srv);
		return 1;
	}

	rc = listen(srv, 128);
	if (rc < 0) {
		fprintf(stderr, "Failed to listen on socket: %d\n", errno);
		close(srv);
		return 1;
	}

	printf("Serving on http://0.0.0.0:%d...\n", LISTEN_PORT);
	while (1) {
		client = accept(srv, NULL, 0);
		if (client < 0) {
			fprintf(stderr, "Failed to accept incoming connection: %d\n", errno);
			continue;
		}

		memset(recvbuf, 0, BUFLEN);
		n = read(client, recvbuf, BUFLEN - 1);
		if (n > 0) {
			/* Handle GET request */
			if (strncmp(recvbuf, "GET", 3) == 0) {
				write(client, reply, strlen(reply));
			} else {
				write(client, not_found, strlen(not_found));
			}
		}

		close(client);
	}

	close(srv);
	return 0;
}
