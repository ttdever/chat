#include "interface.h"
#include "user.h"

void display_welcomeMessage()
{
    display_clearConsole();
    printf(YELLOW_TEXT "-----------CHAT------------\n" RESET_TEXT);
    printf("[USER]: You want to:\n");
    printf("\t1 -> create new user\n");
    printf("\t2 -> create user from memory\n");
    printf("INPUT: ");
    fflush(stdout);

    char userInput;
    scanf("%c", &userInput);
    
    

    printf("[USER]: Your choice is %c\n", userInput);
}

void display_clearConsole()
{
    printf(CLEAR_CONSOLE "\n");
}