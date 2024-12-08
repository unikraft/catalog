#include <stdio.h>
#include <string.h>
#include <zmq.h>

#define BUF_SIZE 256

int main()
{
	void *ctx, *sock;
	char buff[BUF_SIZE];

	ctx = zmq_ctx_new();
	sock = zmq_socket(ctx, ZMQ_REP);

	if (zmq_bind(sock, "tcp://*:5000")) {
		fputs("could not bind to port", stderr);
		return -1;
	}

	while (1) {
		memset(buff, 0, BUF_SIZE);
		zmq_recv(sock, buff, BUF_SIZE - 1, 0);
		printf("Received message: %s\n", buff);
		zmq_send(sock, "ACK", 3, 0);
	}

	return 0;
}
