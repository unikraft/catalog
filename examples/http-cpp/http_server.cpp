/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2023, Unikraft GmbH and the Unikraft Authors.
 */

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define LISTEN_PORT 8080

static std::string reply = "HTTP/1.1 200 OK\r\n" \
			    "Content-Type: text/html\r\n" \
			    "Content-Length: 14\r\n" \
			    "Connection: close\r\n" \
			    "\r\n" \
			    "Hello, World!\n";

#define BUFLEN 2048
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
		std::cerr << "Failed to create socket: " << errno << std::endl;
		goto out;
	}

	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = INADDR_ANY;
	srv_addr.sin_port = htons(LISTEN_PORT);

	rc = bind(srv, (struct sockaddr *) &srv_addr, sizeof(srv_addr));
	if (rc < 0) {
		std::cerr << "Failed to bind socket: " << errno << std::endl;
		goto out;
	}

	/* Accept one simultaneous connection */
	rc = listen(srv, 1);
	if (rc < 0) {
		std::cerr << "Failed to listen on socket: " << errno << std::endl;
		goto out;
	}

	std::cout << "Listening on port " << LISTEN_PORT << std::endl;
	while (1) {
		client = accept(srv, NULL, 0);
		if (client < 0) {
			std::cerr << "Failed to accept incoming connection: " << errno << std::endl;
			goto out;
		}

		/* Receive some bytes (ignore errors) */
		read(client, recvbuf, BUFLEN);

		/* Send reply */
		n = write(client, reply.c_str(), reply.length());
		if (n < 0)
			std::cerr << "Failed to send reply" << std::endl;
		else
			std::cout << "Sent a reply" << std::endl;

		/* Close connection */
		close(client);
	}

out:
	return rc;
}
