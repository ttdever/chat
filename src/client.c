#include "config.h"
#if PROG_MODE == 1

#include "client.h"

int init_client(int argc, char **argv)
{
    SOCKET clientSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL, *ptr = NULL, hints;
    const char *sendbuf = "BEEP BOOP BEEP BOOP!";
    char recvbuf[BUFFER_LEN];
    int call_result;
    int recvbuflen = BUFFER_LEN;
    char *hostname = argc != 2 ? "localhost" : argv[1];

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    call_result = getaddrinfo(hostname, PORT, &hints, &result);
    if (call_result != 0)
    {
        printf("[CLIENT][ERR]: Wasn't able to get addrInfo\n");
        WSACleanup();
        return 1;
    }
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
    {

        clientSocket = socket(ptr->ai_family, ptr->ai_socktype,
                              ptr->ai_protocol);
        if (clientSocket == INVALID_SOCKET)
        {
            printf("[CLIENT][ERR]: Socket init failed");
            WSACleanup();
            return 1;
        }

        call_result = connect(clientSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (call_result == SOCKET_ERROR)
        {
            closesocket(clientSocket);
            clientSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (clientSocket == INVALID_SOCKET)
    {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    call_result = send(clientSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (call_result == SOCKET_ERROR)
    {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    printf("[CLIENT]: Bytes Sent: %d\n", call_result);

    call_result = shutdown(clientSocket, SD_SEND);
    if (call_result == SOCKET_ERROR)
    {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    do
    {

        call_result = recv(clientSocket, recvbuf, recvbuflen, 0);
        if (call_result > 0)
            printf("Bytes received: %d\n", call_result);
        else if (call_result == 0)
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    } while (call_result > 0);

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}

#endif