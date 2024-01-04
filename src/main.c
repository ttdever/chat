#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "config.h"
#include "interface.h"
#include "structs.h"

void test(int argc, char **argv, int *out);

int main(int argc, char **argv)
{
    // display_welcomeMessage();

    CharFunction testFunction = {};

    strcpy(testFunction.input, "test");
    testFunction.function = test;

    int result = 0;

    testFunction.function(argc, argv, &result);
    printf("[SYS]: call result is %d\n", result);

    return 0;
}

void test(int argc, char **argv, int *out)
{
    printf("[SYS]: test has been called\n");
    *out = 1;
}