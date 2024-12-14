/*
 * sock_util.h: useful socket macros and structures
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

#ifndef TESTS_OS_DEMO_SERVER_SOCK_UTIL_H_
#define TESTS_OS_DEMO_SERVER_SOCK_UTIL_H_	1

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

/* default backlog for listen(2) system call */
#define DEFAULT_LISTEN_BACKLOG		5

/* "shortcut" for struct sockaddr structure */
#define SSA			struct sockaddr

int tcp_connect_to_server(const char *name, unsigned short port);
int tcp_close_connection(int s);
int tcp_create_listener(unsigned short port, int backlog);
int get_peer_address(int sockfd, char *buf, size_t len);

#ifdef __cplusplus
}
#endif

#endif  // TESTS_OS_DEMO_SERVER_SOCK_UTIL_H_
