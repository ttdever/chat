#ifndef INTERFACE_H
#define INTERFACE_H

#define RED_TEXT "\033[1;31m"
#define GREEN_TEXT "\033[1;32m"
#define YELLOW_TEXT "\033[1;33m"
#define RESET_TEXT "\033[0m"
#define CLEAR_CONSOLE "\033[2J\033[H"

#include <stdio.h>

void display_welcomeMessage();
void display_clearConsole();

#endif
