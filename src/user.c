#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <shlobj.h>
#include <shlwapi.h>
#include "user.h"

// User struct functions:
User *user_createNewUser(const char *username, const char *ip_address, const char *port)
{
    User *newUser = calloc(1, sizeof(User));

    if (newUser == NULL)
    {
        return NULL;
    }

    if (user_setUsername(newUser, username) != 0 ||
        user_setIpaddress(newUser, ip_address) != 0 ||
        user_setPort(newUser, port) != 0)
    {
        return NULL;
    }

    return newUser;
}

int user_setUsername(User *user, const char *username)
{
    if (username == NULL || strlen(username) > MAX_USERNAME_LENGTH)
    {
        return -1;
    }

    strncpy(user->username, username, strlen(username));
    return 0;
}

int user_setIpaddress(User *user, const char *ip_address)
{
    if (isValidIPv4(ip_address) != 0)
    {
        return -1;
    }

    strncpy(user->ip_address, ip_address, strlen(ip_address));
    return 0;
}

int user_setPort(User *user, const char *port)
{
    if (isValidPort(port))
    {
        return -1;
    }

    strncpy(user->port, port, strlen(port));
    return 0;
}

void user_printUserInfo(User *user)
{
    if (user == NULL)
    {
        printf("[USER]: User is NULL\n");
        return;
    }

    printf("[USER]: USER INFORMATION:\n");
    printf("\tusername: \"%s\"\n", user->username);
    printf("\tip address: \"%s\"\n", user->ip_address);
    printf("\tport: \"%s\"\n", user->port);
}

User user_getUserFromMemory()
{
    User readedUser = {.username = "N/A", .ip_address = "127.0.0.1", .port = "1337"};

    return readedUser;
}

int user_saveUserToMemory(User user)
{
    char pathBuffer[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, pathBuffer)))
    {
        PathAppend(pathBuffer, TEXT("chatApp"));
        CreateDirectoryA(pathBuffer, NULL);

        PathAppend(pathBuffer, TEXT("USER_INFO.txt"));
    }

    HANDLE hFile = CreateFile(pathBuffer, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        CloseHandle(hFile);
        return 1;
    }

    char convertedUser[MAX_USERNAME_LENGTH + 5 + MAX_IP_LENGTH + 3 + MAX_PORT_LENGTH + 5 + 3];
    strcpy(convertedUser, "Name:");
    strcat(convertedUser, user.username);
    strcat(convertedUser, "\n");
    strcat(convertedUser, "ip:");
    strcat(convertedUser, user.ip_address);
    strcat(convertedUser, "\n");
    strcat(convertedUser, "port:");
    strcat(convertedUser, user.port);

    DWORD writtenBytes;
    if (!WriteFile(hFile, convertedUser, strlen(convertedUser), &writtenBytes, NULL))
    {
        CloseHandle(hFile);
        return 1;
    }

    CloseHandle(hFile);
    return 0;
}

// Field specific verifications:
int isValidIPv4(const char *ip_address)
{
    if (ip_address == NULL || strlen(ip_address) < 6 || strlen(ip_address) > MAX_IP_LENGTH)
    {
        return -1;
    }

    int numOfSections = 0;
    int sectionValue = 0;
    int inputLength = strlen(ip_address);

    if (inputLength < 6 + 1 || inputLength > MAX_IP_LENGTH)
    {
        return -1;
    }

    int i;
    for (i = 0; i < inputLength; ++i)
    {
        char currentCharacter = ip_address[i];

        if (currentCharacter == '.' || currentCharacter == '\0')
        {
            if (sectionValue < 0 || sectionValue > 255)
            {
                return -1;
            }

            ++numOfSections;
            sectionValue = 0;
        }
        else if (currentCharacter >= '0' && currentCharacter <= '9')
        {
            sectionValue = sectionValue * 10 + (int)(currentCharacter - '0');
        }
        else
        {
            return -1;
        }
    }

    return numOfSections == 4;
}

int isValidPort(const char *port)
{
    if (port == NULL || strlen(port) == 0 || strlen(port) > MAX_PORT_LENGTH)
    {
        return -1;
    }

    int portLength = strlen(port);

    if (portLength < 1 || portLength > MAX_PORT_LENGTH)
    {
        return -1;
    }

    char *endPointer;
    int portIntValue = strtol(port, &endPointer, 10);

    if (*endPointer != '\0')
    {
        return -1;
    }

    if (portIntValue < 1 || portIntValue > 65535)
    {
        return -1;
    }

    return 0;
}
