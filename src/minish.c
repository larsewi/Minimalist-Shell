
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#include "logger.h"
#include "minish.h"
#include "strarray.h"

#define COLOR_GREEN "\033[1;32m"
#define COLOR_RESET "\033[0m"

#define LIST_DIRECTORY "ls"
#define CHANGE_DIRECTORY "cd"
#define PRINT_WORKING_DIRECTORY "pwd"
#define EXIT_SHELL "exit"
#define EXECUTE_PROGRAM "./"

/**
 * NAME: list_directory - print content of directory
 * DESC: 
 * RETURN: 
 * AUTHOR: Written by Lars Erik Wik
 */
void list_directory(const char** str_array);

void change_directory(const char** str_array);

void print_working_directory(const char** str_array);

void execute_binary(const char** str_array);

void print_prompt() {
    const char* username = getenv("USER");
    if (!username) {
        LOG_WARNING("Failed to retrieve environment variable USER");
        username = "user";
    }
    printf(COLOR_GREEN "%s@minish" COLOR_RESET "$ ", username);
}

enum status get_user_input(char* buffer, int size) {
    buffer = fgets(buffer, size, stdin);
    if (buffer == NULL)
        return feof(stdin) ? Quit : Failure;
    buffer[strlen(buffer) - 1] = '\0';
    return Success;
}

enum status execute_command(char* str) {
    enum status ret = Success;
    char** str_array = split_str(str, " \t");

    if (str_array == NULL) /* If no command */
        return ret;

    else if (!strcmp(str_array[0], LIST_DIRECTORY))
        list_directory(str_array);

    else if (!strcmp(str_array[0], CHANGE_DIRECTORY))
        change_directory(str_array);

    else if (!strcmp(str_array[0], PRINT_WORKING_DIRECTORY))
        print_working_directory(str_array);

    else if (!strcmp(str_array[0], EXIT_SHELL))
        ret = Quit;

    else
        execute_binary(str_array);

    free_str_array(str_array);

    return ret;
}

/**
 * TODO: add color scheme to output in order to differentiate file types
 * TODO: add argument feature (e.g. what and where to print)
 */
void list_directory(const char** str_array) {
    LOG_DEBUG("Argument count: %d", str_array_len(str_array));
    if (str_array_len(str_array) > 1) {
        printf("minish: cd: too many arguments\n");
        return;
    }

    DIR* directory = opendir(".");
    struct dirent* dirent;

    if (directory == NULL) {
        perror("Failed to open current working directory: %s");
        return;
    }

    dirent = readdir(directory);
    while (dirent != NULL) {
        printf("%s\n", dirent->d_name);
        dirent = readdir(directory);
    }
    closedir(directory);
}

void change_directory(const char** str_array) {
    if (str_array_len(str_array) > 2)
        printf("minish: cd: too many arguments\n");
    else if (chdir(str_array[1]) == -1)
        perror("minish: cd");
}

void print_working_directory(const char** str_array) {
    if (str_array_len(str_array) > 1) {
        printf("minish: cd: too many arguments\n");
        return;
    }

    char* cwd = getcwd(NULL, 0);
    if (!cwd) {
        perror("minish: cd");
        return;
    }

    printf("%s\n", cwd);
    free(cwd);
}

void execute_binary(const char** str_array) {
    pid_t child_pid;
    int child_status;

    LOG_DEBUG("Forking process");
    child_pid = fork();
    if (child_pid == 0) {
        /* This is the child */
        execv(str_array[0], str_array);
        /* The  exec() functions return only if an error has occurred.  */
        printf("Command '%s' not found\n", str_array[0]);
    } else {
        pid_t some_child;
        do {
            some_child = wait(&child_status);
            if (some_child == child_pid)
                LOG_DEBUG("Child process terminated");
        } while (some_child != child_pid);
    }
}
