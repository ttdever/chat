#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_INPUT_LENGTH 16

typedef struct CharFunction
{
    char input[MAX_INPUT_LENGTH];
    void (*function)(int argc, char **argv, void *out);
} CharFunction;

#endif
