#include "helper.h"
#include "interface.h"
#include "user.h"
#include "globals.h"

const CharFunction welcomeFunctions[2] = {
    {.input = "1", .function = display_createUser},
    {.input = "2", .function = display_readUserFromMem}};

void display_welcomeMessage()
{
    display_clearConsole();
    printf(YELLOW_TEXT "--------------CHAT---------------\n" RESET_TEXT);
    printf(YELLOW_TEXT "[SYS]: Started\n" RESET_TEXT);
    printf("[USER]: You want to:\n");
    printf("\t1 -> create new user\n");
    printf("\t2 -> read user from memory\n");
    printf(GREEN_TEXT "INPUT: " RESET_TEXT);
    fflush(stdout);

    char userInput[3] = {};
    fgets(userInput, 3, stdin);
    userInput[strlen(userInput) - 1] = '\0';

    void (*functionToCall)(int, char, void *) = getFunctionFromInput(userInput, welcomeFunctions, 2);
    if (functionToCall == NULL)
    {
        printf("[USER][ERR]: No such function\n");
        exit(1);
    }

    functionToCall(0, '\0', NULL);
}

void display_createUser(int argc, char **argv, void *out)
{
    (void)argc;
    (void)argv;
    (void)out;

    User *newUser = calloc(sizeof(User), 1);

    if (currentUser == NULL)
    {
        currentUser = calloc(sizeof(User), 1);
        if (currentUser == NULL)
        {
            printf(RED_TEXT "[USER][ERR]: Failed to allocate memmory for user\n" RESET_TEXT);
            exit(1);
        }
    }

    printf(YELLOW_TEXT "[SYS]: Creating a new user\n" RESET_TEXT);
    printf("[USER]: Enter new username:\n");
    printf(GREEN_TEXT "INPUT: " RESET_TEXT);
    fflush(stdout);

    char newUsername[MAX_USERNAME_LENGTH];
    fgets(newUsername, MAX_USERNAME_LENGTH, stdin);
    newUsername[strlen(newUsername) - 1] = '\0';

    strcpy(newUser->username, newUsername);
    strcpy(newUser->ip_address, "127.0.0.1");
    strcpy(newUser->port, "1337");

    currentUser = newUser;
    user_saveUserToMemory(*currentUser);
}

void display_readUserFromMem(int argc, char **argv, void *out)
{
    (void)argc;
    (void)argv;
    (void)out;
}

void display_clearConsole()
{
    printf(CLEAR_CONSOLE "\n");
}