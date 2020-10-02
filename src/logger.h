
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdarg.h>

#if NDEBUG
#define LOG_ERROR(...)
#else
#define LOG_ERROR(...) \
log_f(__FILE__, __func__, __LINE__, "ERROR", LOGGER_ERROR_COLOR, stderr, __VA_ARGS__)
#endif

#if NDEBUG
#define LOG_WARNING(...)
#else
#define LOG_WARNING(...) \
log_f(__FILE__, __func__, __LINE__, "WARNING", LOGGER_WARNING_COLOR, stdout, __VA_ARGS__)
#endif

#if NDEBUG
#define LOG_INFO(...)
#else
#define LOG_INFO(...) \
log_f(__FILE__, __func__, __LINE__, "INFO", LOGGER_INFO_COLOR, stdout, __VA_ARGS__)
#endif

#if NDEBUG
#define LOG_DEBUG(...)
#else
#define LOG_DEBUG(...) \
log_f(__FILE__, __func__, __LINE__, "DEBUG", LOGGER_DEBUG_COLOR, stdout, __VA_ARGS__)
#endif

#define LOGGER_CLEAR_COLOR "\x1B[0m"
#define LOGGER_ERROR_COLOR "\x1B[31m"
#define LOGGER_WARNING_COLOR "\x1B[33m"
#define LOGGER_INFO_COLOR "\x1B[35m"
#define LOGGER_DEBUG_COLOR "\x1B[36m"

void log_f(const char *file, const char *func, int line, const char *type, 
           const char *color, FILE *filePtr, const char *format, ...);
    
#endif