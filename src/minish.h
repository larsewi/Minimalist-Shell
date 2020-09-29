
#ifndef MINISH_H
#define MINISH_H

#include <stdbool.h>

struct command {
    unsigned int argc;     /* argument count    */
    char** args;           /* arguments         */
    bool bg;               /* run in background */
};

char* prompt(char* buffer, int size);

struct command* parse(const char* str);

void execute(struct command* cmd, unsigned int count);

void clean(struct command* command);

#endif
