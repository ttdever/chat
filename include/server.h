#include "config.h"
#if PROG_MODE == 0
#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

extern SOCKET serverSocket;
extern SOCKET clientSocket;

extern struct addrinfo *result;
extern struct addrinfo hints;

#define SOCKET_ADDRESS_FAMILY AF_INET // IP_V4
#define SOCKET_TYPE SOCK_STREAM       // STREAM
#define SOCKET_PROTOCOL IPPROTO_TCP   // TCP

#define BUFFER_LEN 512

int init_server();
int handle();

#endif
#endif
