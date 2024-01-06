#ifndef INTERFACE_H
#define INTERFACE_H

#define RED_TEXT "\033[1;31m"
#define GREEN_TEXT "\033[1;32m"
#define YELLOW_TEXT "\033[1;33m"
#define RESET_TEXT "\033[0m"
#define CLEAR_CONSOLE "\033[2J\033[H"

#include <stdio.h>
#include <string.h>
#include "structs.h"

extern const CharFunction welcomeFunctions[2];

void display_welcomeMessage();
void display_clearConsole();

void display_createUser(int argc, char **argv, void *out);
void display_readUserFromMem(int argc, char **argv, void *out);

#endif
