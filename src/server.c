#include "config.h"
#if PROG_MODE == 0
#include "server.h"

SOCKET serverSocket = INVALID_SOCKET;
SOCKET clientSocket = INVALID_SOCKET;

struct addrinfo *result = NULL;
struct addrinfo hints;

int init_server()
{
    printf("[SYS]: Starting in server mode...\n");

    serverSocket = socket(
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
    freeaddrinfo(result);
    printf("[SERVER]: Socket binded\n");

    call_result = listen(serverSocket, SOMAXCONN);
    if (call_result == SOCKET_ERROR)
    {
        printf("[SERVER]: Wasn't able to start listening on socket -> aborting\n");
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }
    printf("[SERVER]: Listening\n");

    clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET)
    {
        printf("[SERVER]: Wasn't able to accept client\n");
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    closesocket(serverSocket);
    return handle();
}

int handle()
{
    int call_result, call_send_result;
    int bufferLength = BUFFER_LEN;
    char recvBuffer[BUFFER_LEN];

    int recievedLength;
    int sendLength;

    do
    {
        recievedLength = recv(clientSocket, recvBuffer, bufferLength, 0);
        if (recievedLength > 0)
        {
            printf("[SERVER]: Recieved %d bytes\n", recievedLength);

            printf("[SERVER][IN]: Recieved message:");
            for (int i = 0; i < recievedLength; ++i)
            {
                printf("%c", recvBuffer[i]);
            }
            printf("\n");

            sendLength = send(clientSocket, recvBuffer, recievedLength, 0);
            if (sendLength == SOCKET_ERROR)
            {
                printf("[SERVER][ERR]: Wasn't able to send response\n");
                closesocket(clientSocket);
                WSACleanup();
                return -1;
            }
            printf("[SERVER]: Sent %d bytes in response\n", sendLength);
        }
        else if (recievedLength == 0)
        {
            printf("[SERVER]: Closing connection...\n");
        }
        else
        {
            printf("[SERVER][ERR]: Failed to recieve data from client -> aborting");
            closesocket(clientSocket);
            WSACleanup();
            return -1;
        }

    } while (recievedLength > 0);

    call_result = shutdown(clientSocket, SD_SEND);
    if (call_result == SOCKET_ERROR)
    {
        printf("[SERVER] Shutdown failed");
        closesocket(clientSocket);
        WSACleanup();
        return -1;
    }

    return 0;
}

#endif