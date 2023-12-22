#include "config.h"
#if PROG_MODE == 0
#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

int init_server();

#endif
#endif
