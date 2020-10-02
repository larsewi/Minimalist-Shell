
#ifndef MINISH_H
#define MINISH_H

enum status {
    Success, /* Shell should keep running */
    Failure, /* An error has occured      */
    Quit     /* Shell should stop running */
};

void print_prompt();

enum status get_user_input(char* buffer, int size);

enum status execute_command(char* command);

#endif
