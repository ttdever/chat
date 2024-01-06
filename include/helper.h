#ifndef HELPER_H
#define HELPER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structs.h"

void *getFunctionFromInput(const char *input, const CharFunction *functions, const int functionsLength);

#endif
