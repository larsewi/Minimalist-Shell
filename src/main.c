
/**
 * main.c
 * Lars Erik Wik
 * 29/09/2020
 * 
 * Read Eval Print Loop for Minimalist Shell.
 */

#include <stdio.h>
#include <stdlib.h>

#include "logger.h"
#include "minish.h"

#define MAX_INPUT_SIZE 4096


/**
 * Entry point for Minimalist Shell.
 * Prompts user and reads input from user stored in a 4 KiB buffer.
 * Input is then parsed in to a shell command and executed.
 */
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
