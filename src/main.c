
/**
 * main.c
 * Lars Erik Wik
 * 29/09/2020
 */

#include <stdio.h>

#include "logger.h"

int main(int argc, const char** argv) {
    printf("Hello, world!\n");
    
    LOG_DEBUG("Hello %s", "there");
    LOG_INFO("%d, %d, %d", 1, 2, 3);
    LOG_WARNING("This i a nullptr %p", NULL);
    LOG_ERROR("Yes");
    return 0;
}
