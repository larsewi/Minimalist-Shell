
/**
 * main.c
 * Lars Erik Wik
 * 29/09/2020
 * 
 * REPL
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "logger.h"
#include "minish.h"

#define MAX_INPUT_SIZE 4096


int main(void) {
    enum status ret;
    char input_buffer[MAX_INPUT_SIZE];

    do {
        print_prompt();

        ret = get_user_input(input_buffer, MAX_INPUT_SIZE);

        if (ret == Success)
            ret = execute_command(input_buffer);
        
    } while (ret == Success);

    if (ret == Quit) {
        LOG_INFO("Exit success");
        return EXIT_SUCCESS;
    } 
    LOG_ERROR("Exit failure");
    return EXIT_FAILURE;
}
