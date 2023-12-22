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
        printf("[SERVER][ERR]: Wasn't able to initialize a socket -> aborting\n");
        return -1;
    }
    printf("[SERVER]: Socket initialized!\n");

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = SOCKET_ADDRESS_FAMILY;
    hints.ai_socktype = SOCKET_TYPE;
    hints.ai_protocol = SOCKET_PROTOCOL;
    hints.ai_flags = AI_PASSIVE;

    int call_result = getaddrinfo(NULL, PORT, &hints, &result);
    if (call_result != 0)
    {
        printf("[SERVER][ERR]: Wasn't able to get addrInfo -> aborting\n");
        WSACleanup();
        return -1;
    }
    printf("[SERVER]: Got addrInfo\n");

    call_result = bind(serverSocket, result->ai_addr, (int)result->ai_addrlen);
    if (call_result == SOCKET_ERROR)
    {
        printf("[SERVER][ERR]: Wasn't able to bind socket -> aborting\n");
        freeaddrinfo(result);
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }
    printf("[SERVER]: Socket binded");

    return 0;
}

#endif