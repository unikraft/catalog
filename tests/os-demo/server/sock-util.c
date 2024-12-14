/*
 * sock_util.c: useful socket functions
 *
 * Copyright (c) 2008-2011, Razvan Deaconescu, razvan.deaconescu@cs.pub.ro
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#include "./util.h"
#include "./debug.h"
#include "./sock-util.h"

/*
 * Connect to a TCP server identified by name (DNS name or dotted decimal
 * string) and port.
 */

int tcp_connect_to_server(const char *name, unsigned short port)
{
	struct hostent *hent;
	struct sockaddr_in server_addr;
	int s;
	int rc;

	hent = gethostbyname(name);
	DIE(hent == NULL, "gethostbyname");

	s = socket(PF_INET, SOCK_STREAM, 0);
	DIE(s < 0, "socket");

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	memcpy(&server_addr.sin_addr.s_addr, hent->h_addr,
			sizeof(server_addr.sin_addr.s_addr));

	rc = connect(s, (struct sockaddr *) &server_addr, sizeof(server_addr));
	DIE(rc < 0, "connect");

	return s;
}

int tcp_close_connection(int sockfd)
{
	int rc;

	rc = shutdown(sockfd, SHUT_RDWR);
	DIE(rc < 0, "shutdown");

	return close(sockfd);
}

/*
 * Create a server socket.
 */

int tcp_create_listener(unsigned short port, int backlog)
{
	struct sockaddr_in address;
	int listenfd;
	int sock_opt;
	int rc;

	listenfd = socket(PF_INET, SOCK_STREAM, 0);
	DIE(listenfd < 0, "socket");

	sock_opt = 1;
	rc = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,
				&sock_opt, sizeof(int));
	DIE(rc < 0, "setsockopt");

	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = INADDR_ANY;

	rc = bind(listenfd, (SSA *)&address, sizeof(address));
	DIE(rc < 0, "bind");

	rc = listen(listenfd, backlog);
	DIE(rc < 0, "listen");

	return listenfd;
}

/*
 * Use getpeername(2) to extract remote peer address. Fill buffer with
 * address format IP_address:port (e.g. 192.168.0.1:22).
 */

int get_peer_address(int sockfd, char *buf, size_t len)
{
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(struct sockaddr_in);

	if (getpeername(sockfd, (SSA *)&addr, &addrlen) < 0)
		return -1;

	snprintf(buf, len, "%s:%d", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

	return 0;
}
