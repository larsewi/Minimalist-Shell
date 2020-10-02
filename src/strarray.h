
#ifndef STRARRAY_H
#define STRARRAY_H

char* sub_str(char* dest, const char* src, unsigned int from, unsigned int to);

char** split_str(const char* src, const char* delim);

unsigned int count_token(const char* src, const char* delim);

unsigned int str_array_len(const char** str_array);

void free_str_array(char** str_array);

#endif
