#if PROG_MODE == 1
#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

int init_client(int argc, char **argv);
#define BUFFER_LEN 512

#endif
#endif
