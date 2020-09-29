
/**
 * main.c
 * Lars Erik Wik
 * 29/09/2020
 */

#include <stdio.h>
#include <stdlib.h>

#include "logger.h"
#include "minish.h"

#define MAX_INPUT_SIZE 10240u

/**
 * TODO - Handle interrupt signals
 */

int main(int argc, const char** argv) {
    char answer[MAX_INPUT_SIZE];
    
    if (!prompt(answer, MAX_INPUT_SIZE)) {
        LOG_ERROR("Prompt failed");
        exit(EXIT_FAILURE);
    }
    LOG_DEBUG("Input from user: %s", answer);

    return EXIT_SUCCESS;
}
