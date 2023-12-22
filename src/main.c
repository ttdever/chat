#include <stdio.h>
#include "config.h"

#if PROG_MODE == 0
#include "server.h"
#elif PROG_MODE == 1
#include "client.h"
#endif

WSADATA wsaData;

#pragma comment(lib, "ws2_32")

int main()
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
    return init_server();
#elif PROG_MODE == 1
#include "client.h"
#endif
}