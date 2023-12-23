// This struct represent user in chat:
#ifndef USER_H
#define USER_H

#define MAX_USERNAME_LENGTH 32
#define MAX_IP_LENGTH 16
#define MAX_PORT_LENGTH 6

typedef struct User
{
    char username[MAX_USERNAME_LENGTH];
    char ip_address[MAX_IP_LENGTH];
    char port[MAX_PORT_LENGTH];
} User;

User *user_createNewUser(const char *username, const char *ip_address, const char *port);
int user_setUsername(User *user, const char *username);
int user_setIpaddress(User *user, const char *ip_address);
int user_setPort(User *user, const char *port);
void user_printUserInfo(User *user);

int isValidIPv4(const char *ip_address);
int isValidPort(const char *port);
#endif
