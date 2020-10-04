
/**
 * minish.h
 * Lars Erik Wik
 * 29/09/2020
 */

#ifndef MINISH_H
#define MINISH_H

/**
 * A return status code that indicates what the REPL should do after  returning
 * of a callee.
 */
enum status {
    Success, /* Shell should keep running */
    Quit,    /* Shell should stop running */
    Failure  /* An error has occured and should be handeled */
};

/**
 * Print prompt containing user name followed by '@minish: '. Prompt is printed
 * in a bold green color scheme.
 * 
 * Returns an enum status code, see 'minish.h: enum status' for more info.
 */
enum status print_prompt(void);

/**
 * Reads at moast one less then 'size' characters from input stream 'stdin' and
 * stores it in to a buffer pointed to by 'buffer'. Reading stops after an  EOF
 * (indicating no more input) or a newline. If a newline is read,  the  newline
 * character is swapped with a terminating nullbyte. EOF is usually  caused  by 
 * the user pressing CTRL + D.
 * 
 * Returns an enum status code, see 'minish.h: enum status' for more info.
 */
enum status get_user_input(char* buffer, int size);

/**
 * Parses and executes a command pointet to by 'str'. Command may  be  executed
 * as a built in command running in this process or an external binary  running
 * in a child process.
 * 
 * Returns an enum status code, see 'minish.h: enum status' for more info.
 */
enum status execute_command(char* str);

#endif
