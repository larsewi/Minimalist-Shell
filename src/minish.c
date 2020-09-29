
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "logger.h"
#include "minish.h"

#define COLOR_GREEN "\033[1;32m"
#define COLOR_RESET "\033[0m"

#define DELIMITOR " \t"

void print_prompt();
struct command* parse_command(const char* str);
void print_working_directory();

char* prompt(char* buffer, int size) {
    print_prompt();

    if(!fgets(buffer, size, stdin)) {
        LOG_ERROR("Failed to retrieve user input");
        return NULL;
    }

    buffer[strlen(buffer) - 1] = '\0'; /* Remove newline */
    return buffer;
}

struct command* parse(const char* str) {
    char buffer[strlen(str)];

    /* Allocate space for command */
    struct command* command = malloc(sizeof(struct command));
    if (!command) {
        LOG_ERROR("Failed to allocate memory");
        return NULL;
    }

    /* Count number of arguments */
    strcpy(buffer, str);
    command->argc = 0;
    char* token = strtok(buffer, DELIMITOR);
    while (token) {
        command->bg = strcmp(token, "&") == 0;
        command->argc++;
        token = strtok(NULL, DELIMITOR);
    }

    /* The '&' is not an argument */
    if (command->bg) {
        LOG_DEBUG("Run in background");
        command->argc--;
    }
    LOG_DEBUG("Argument count: %d", command->argc);

    /* Allocate space for arguments*/
    command->args = malloc(sizeof(char*) * command->argc);

    /* Parse arguments */
    unsigned int i;
    strcpy(buffer, str);
    token = strtok(buffer, DELIMITOR);
    for (i = 0; i < command->argc; i++) {
        LOG_DEBUG("Parse argument: %s", token);
        command->args[i] = malloc(strlen(token) + 1);
        strcpy(command->args[i], token);
        token = strtok(NULL, DELIMITOR);
    }

    return command;
}

void clean(struct command* command) {
    LOG_DEBUG("Cleaning up");

    unsigned int i;
    for (i = 0; i < command->argc; i++) {
        free(command->args[i]);
    }
    free(command->args);
    free(command);
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
     * the returned buffer. (Linux Programmer's Manual, 2018-04-30)
     */
    char* cwd = getcwd(NULL, 0);
    if (!cwd) {
        LOG_ERROR("Failed to retrieve current working directory: %s", errno);
        return;
    }
    printf("%s\n", cwd);
    free(cwd);
}
