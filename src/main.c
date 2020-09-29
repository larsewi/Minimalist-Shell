
/**
 * main.c
 * Lars Erik Wik
 * 29/09/2020
 */

#include <stdio.h>
#include <stdlib.h>

#include "logger.h"
#include "minish.h"

#define INPUT_BUFFER_SIZE 10240

/**
 * TODO - Handle interrupt signals
 */

int main(void) {
    char input_buffer[INPUT_BUFFER_SIZE];
    
    if (!prompt(input_buffer, INPUT_BUFFER_SIZE)) {
        LOG_ERROR("Prompt failed");
        exit(EXIT_FAILURE);
    }
    LOG_DEBUG("Input from user: %s", input_buffer);

    struct command* command = parse(input_buffer);
    if (!command) {
        LOG_ERROR("Parsing failed");
        exit(EXIT_FAILURE);
    }

    clean(command);

    return EXIT_SUCCESS;
}
