#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "config.h"
#include "user.h"

int main(int argc, char **argv)
{
    User *normalUser = user_createNewUser("Bob Kerman", "1.3.3.7", "69");
    User *wrongUser_ip = user_createNewUser("Booba", "ip addres", "132");
    User *wrongUser_port = user_createNewUser("Booba2", "2.2.2.2", "port");

    user_printUserInfo(normalUser);
    printf("--------------------\n");
    user_printUserInfo(wrongUser_ip);
    printf("--------------------\n");
    user_printUserInfo(wrongUser_port);

    return 0;
}