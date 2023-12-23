#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "config.h"

#if PROG_MODE == 0
#include "server.h"
#elif PROG_MODE == 1
#include "client.h"
#endif

WSADATA wsaData;

int main(int argc, char **argv)
{
    printf("[SYS]: Started\n");

    // Init WSAS:
    int wsaInitResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaInitResult != 0)
    {
        printf("[SYS][ERROR]: Wasn't able to initialize WSA -> aborting\n");
        return 1;
    }

    printf("[SYS]: WSA initialized\n");

#if PROG_MODE == 0
    init_server();
#elif PROG_MODE == 1
    init_client(argc, argv);
#endif

    return 0;
}