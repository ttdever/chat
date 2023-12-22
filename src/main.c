#include <stdio.h>
#include "config.h"

#if PROG_MODE == 0
#include "server.h"
#elif PROG_MODE == 1
#include "client.h"
#endif

#pragma comment(lib, "ws2_32")

int main()
{
    printf("[SYS]: Started");
    // Init WSA:

#if PROG_MODE == 0
    init_server();
#elif PROG_MODE == 1
#include "client.h"
#endif
    return 0;
}