
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strarray.h"
#include "logger.h"

char* sub_str(char* dest, const char* src, unsigned int from, unsigned int to) {
    unsigned int i = from;

    if (!src) return NULL;
    if (!dest) dest = malloc(to + 1 - from);

    while (i++ < from && src[i] != '\0')
        dest[i] = src[i];
    dest[i] = '\0';

    return dest;
}

char** split_str(const char* src, const char* delim) {
    unsigned int count, i;
    char str[strlen(src) + 1];
    char* token;
    char** str_array;

    /* Count number of tokens in string */
    count = count_token(src, delim);
    LOG_DEBUG("Num tokens: %d", count);
    if (!count) return NULL;

    /* Allocate space for string array */
    str_array = malloc(sizeof(char*) * (count + 1));
    str_array[count] = NULL; /* Array terminated by NULL */

    /* Split string */
    i = 0;
    strcpy(str, src);
    token = strtok(str, delim);
    while (token != NULL) {
        LOG_DEBUG("Token %d: %s", i, token);
        str_array[i] = malloc(strlen(token) + 1);
        strcpy(str_array[i++], token);
        token = (strtok(NULL, delim));
    }

    return str_array;
}

unsigned int count_token(const char* src, const char* delim) {
    unsigned int count;
    char str[strlen(src) + 1];
    char* token;

    /* Count number of tokens in string */
    count = 0;
    strcpy(str, src);
    token = strtok(str, delim);
    while (token != NULL) {
        ++count;
        token = strtok(NULL, delim);
    }

    return count;
}

unsigned int str_array_len(const char** str_array) {
    unsigned int len = 0;

    while (str_array[len] != NULL) ++len;
    return len; 
}

void free_str_array(char** str_array) {
    int i = 0;

    while (str_array[i] != NULL) {
        free(str_array[i++]);
    }
    free(str_array[i]);
    free(str_array);
}
