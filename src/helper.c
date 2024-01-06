#include "helper.h"

void *getFunctionFromInput(const char *input, const CharFunction *functions, const int functionsLength)
{
    if (input == NULL || functions == NULL || functionsLength == 0)
    {
        return NULL;
    }

    int i;
    for (i = 0; i < functionsLength; ++i)
    {
        if (functions[i].function == NULL)
        {
            return NULL;
        }

        if (strcmp(input, functions[i].input) == 0)
        {
            return functions[i].function;
        }
    }

    return NULL;
}
