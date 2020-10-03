# Minimalist-Shell

## Table of Contents

* [About the Project](#about-the-project)
* [Compile](#compile)
* [Usage](#usage)
  * [List directory](#list-directory)
  * [Change directory](#change-directory)
  * [Print working directory](#print-working-directory)
* [Debug](#debug)

## About the project 
This project was given to me as a homework assignment before a technical interview with Northern Tech.

## Compile
The project can be compiled using make by calling ```$ make``` from the project root directory.

The binaries can be removed by calling ```$ make clean```

## Usage
To run the project call ```$ make run``` or ```$ ./minish```. from the project root directory. 
You will now see the prompt has changed to "\<YOUR_USER_NAME\>@minish: ".
From here you can call the commands ```ls```, ```cd``` and ```pwd``` or you can execute a binary in your
working directory.

### List directory
The command ```ls``` takes zero arguments and lists files in the current working directory.

```$ ls```

### Change directory
The command ```cd``` takes one or zero arguments and will change the current working directory.
In case of no arguments the current working directory is set to home. In case of one argument
the current working directory is set to the absolute or relative path specified in the argument.

```$ cd <PATH>```

### Print working directory
The command ```cd``` takes zero arguments and lists the current working directory.

```$ pwd```

### Execute binary
To execute a binary, change directory to where the binary is located and call the binary name followed by
the binary arguments.

```$ <BINARY_NAME> <ARGUMENTS>...```

The binary is executed in a child process. The shell waits for the process to exit and prints the status for the user to examine. The exit code is retrieved by using the macros ```WIFEXITED``` and ```WEXITSTATUS``` on a status integer set by the ```wait``` function.

## Debug
To enable debug messages set the macro ```NDEBUG``` to 0 and recompile.

To run a memory leak check, call

```$ make leakcheck```
