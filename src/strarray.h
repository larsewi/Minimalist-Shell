
/**
 * strarray.h
 * Lars Erik Wik
 * 29/09/2020
 */

#ifndef STRARRAY_H
#define STRARRAY_H

/**
 * Copies the characters pointed to by 'src' from index 'from'  to  index  'to'
 * into the buffer pointed to by 'dest'. If buffer 'dest' is NULL,  the  callee
 * dynamically allocates ('to' + 1 - 'from') bytes to the buffer  using  malloc
 * and stores the address in 'dest'. The caller should then free  the  returned 
 * buffer. The callee returns a pointer to sub string or 'NULL' if an error has
 * occured.
 */
char* sub_str(char* dest, const char* src, unsigned int from, unsigned int to);

/**
 * Breaks a string into an array of strings. The string to be parsed should  be
 * specified by 'src'. The 'delim' argument specifies a set of characters  that
 * delimits the tokens in the parsed string. The callee  dynamically  allocates
 * memory to hold the tokens (using malloc), pluss a terminating 'NULL' pointer
 * indicating end of string array. A buffer is dynamically allocated  for  each
 * token in the string array in which the tokens are copied. The caller  should
 * call 'free_str_array' in order free all allocated memory from the heap.  The
 * callee returns a pointer to the string array  or  'NULL'  if  the  delimitor
 * could not produce any tokens.
 */
char** split_str(const char* src, const char* delim);

/**
 * Counts number of tokens generated from breaking a string specified by  'src'
 * using the argument 'delim' which specifies a set of characters that delimits
 * the tokens in a parsed string. Callee returns an  unsigned  int  representig
 * the number of tokens generated.
 */
unsigned int count_token(const char* src, const char* delim);

/**
 * Counts the number of elements in a string array, excluding  the  terminating
 * 'NULL' pointer. Callee returns an  unsigned  int  representing  the  element
 * count.
 */
unsigned int str_array_len(char** str_array);

/**
 * Calls free en each element in the string array  pointed  to  by  'str_array'
 * including the 'NULL' pointer. Then calls free in the string array it self.
 */
void free_str_array(char** str_array);

#endif
