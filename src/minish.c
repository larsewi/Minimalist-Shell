
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "logger.h"
#include "minish.h"

#define COLOR_GREEN "\033[1;32m"
#define COLOR_RESET "\033[0m"

void print_prompt();
void print_working_directory();

char* prompt(char* answer, unsigned int size) {
    print_prompt();

    if(!fgets(answer, size, stdin)) {
        LOG_ERROR("Failed to retrieve user input");
        return NULL;
    }

    answer[strlen(answer) - 1] = '\0'; /* Remove newline */
    return answer;
}

void print_prompt() {
    const char* user = getenv("USER");
    if (!user) {
        LOG_WARNING("Failed to retrieve environment variable USER");
        user = "user";
    }
    printf(COLOR_GREEN "%s@minish" COLOR_RESET "$ ", user);
}

void print_working_directory() {
    /** 
     * As an extension to the POSIX.1-2001 standard,  glibc's  getcwd()  allo‐
     * cates  the  buffer dynamically using malloc(3) if buf is NULL.  In this
     * case, the allocated buffer has the length size  unless  size  is  zero,
     * when  buf  is allocated as big as necessary.  The caller should free(3)
     * the returned buffer. (Linux Programmer's Manual)
     */
    char* cwd = getcwd(NULL, 0);
    if (!cwd) {
        LOG_ERROR("Failed to retrieve current working directory: %s", errno);
        return;
    }
    printf("%s\n", cwd);
    free(cwd);
}
