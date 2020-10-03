
/**
 * logger.c
 * Lars Erik Wik
 * 29/09/2020
 */

#include <stdarg.h>

#include "logger.h"


void log_f(const char *file, const char *func, int line, const char *type, 
           const char *color, FILE *fileptr, const char *format, ...) {
    va_list ap;
    va_start(ap, format);

    fprintf(fileptr, "[%s%s%s][%s:%d in %s]: ", color, type, LOGGER_CLEAR_COLOR, file, line, func);
    vfprintf(fileptr, format, ap);
    fprintf(fileptr, "\n");

    va_end(ap);
}
