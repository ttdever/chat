#ifndef CONFIG_H
#define CONFIG_H

#define PROG_MODE 0 // 0 -> Server | 1 -> Client
#define PORT 1337

#if PROG_MODE == 0
#include <winsock2.h>

#define SOCKET_ADDRESS_FAMILY AF_INET // IP_V4
#define SOCKET_TYPE SOCK_STREAM       // STREAM
#define SOCKET_PROTOCOL IPPROTO_TCP   // TCP

#elif PROG_MODE == 1
#endif

#endif