#include "config.h"
#if PROG_MODE == 0
#include "server.h"

int init_server()
{
    printf("[SYS]: Starting in server mode...\n");

    SOCKET serverSocket = socket(
        SOCKET_ADDRESS_FAMILY,
        SOCKET_TYPE,
        SOCKET_PROTOCOL);

    if (serverSocket == INVALID_SOCKET)
    {
        printf("[SERVER][ERR]: Wasn't able to initialize a socket -> aborting");
        return -1;
    }

    printf("[SERVER]: Socket initialized!");

    return 0;
}

#endif