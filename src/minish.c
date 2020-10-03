
/**
 * minish.c
 * Lars Erik Wik
 * 29/09/2020
 */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>

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
 * Prints a list of all files in the current working directory to  'stdout'. If
 * an error occurs an error  message  is  printed  to  'stderr'.  Currently  no
 * arguments are supported.
 */
void list_directory(char** str_array);

/**
 * Change current working directory. If en error occurs  an  error  message  is
 * printed to 'stderr'.
 */
void change_directory(char** str_array);

/**
 * Prints the absolute path to the current working directory to 'stdout'. If an
 * error occurs an error message is instead printed to 'stderr'.
 */
void print_working_directory(char** str_array);

/**
 * Executes a binary in a child process and waits for the child  to  terminate.
 * The childs exit code is then printed to 'stdout'.
 */
void execute_binary(char** str_array);

void print_prompt(void) {
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
void list_directory(char** str_array) {
    LOG_DEBUG("Argument count: %d", str_array_len(str_array));
    if (str_array_len(str_array) > 1) {
        printf("minish: cd: too many arguments\n");
        return;
    }

    DIR* directory = opendir(".");
    struct dirent* dirent;

    if (directory == NULL) {
        /* print message "minish: cd: <arg1>: <error msg>" */
        const char* src = "minish: cd: ";
        char dest[strlen(src) + strlen(str_array[1]) + 1];
        perror(strcat(strcpy(dest, src), str_array[1]));
        return;
    }

    dirent = readdir(directory);
    while (dirent != NULL) {
        printf("%s\n", dirent->d_name);
        dirent = readdir(directory);
    }
    closedir(directory);
}

void change_directory(char** str_array) {
    if (str_array_len(str_array) > 2)
        fprintf(stderr, "minish: cd: too many arguments\n");
    else if (str_array_len(str_array) == 1) {
        const char* username = getenv("USER");
        char path[strlen("/home/") + strlen(username) + 2];

        strcpy(path, "/home/");
        strcat(path, username);

        if (chdir(path) == -1) {
            LOG_INFO("Failed to change working directory to '%s'", path);
            perror("minish: cd");
            return;
        }
    } else {
        if (chdir(str_array[1]) == -1) {
            LOG_INFO("Failed to set path '%s'", str_array[1]);
            perror("minish: cd");
            return;
        }
    }
}

void print_working_directory(char** str_array) {
    if (str_array_len(str_array) > 1) {
        fprintf(stderr, "minish: cd: too many arguments\n");
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

/**
 * TODO: prevent possible fork bomb
 */
void execute_binary(char** str_array) {
    pid_t child_pid;
    int child_status;

    child_pid = fork();

    if (child_pid == 0) {
        /* This is the child */
        execv(str_array[0], str_array);
        /* Execution did not succeed */
        fprintf(stderr, "Command '%s' not found\n", str_array[0]);
        exit(EXIT_FAILURE);
    } else {
        pid_t some_child;
        do {
            some_child = wait(&child_status);
            if (some_child == child_pid){
                LOG_DEBUG("Child process terminated");
            }
        } while (some_child != child_pid);

        if (WIFEXITED(child_status))
            printf("Process terminated with exit code %d\n", WEXITSTATUS(child_status));
    }
}
