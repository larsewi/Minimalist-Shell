
#include <stdio.h>
#include <stdarg.h>

#ifdef NDEBUG
#define LOG_ERROR(...) \
log_f(__FILE__, __func__, __LINE__, "ERROR", LOGGER_ERROR_COLOR, stderr, __VA_ARGS__)
#else
#define LOG_ERROR(...)
#endif

#ifdef NDEBUG
#define LOG_WARNING(...) \
log_f(__FILE__, __func__, __LINE__, "WARNING", LOGGER_WARNING_COLOR, stdout, __VA_ARGS__)
#else
#define LOG_WARNING(...)
#endif

#ifdef NDEBUG
#define LOG_INFO(...) \
log_f(__FILE__, __func__, __LINE__, "INFO", LOGGER_INFO_COLOR, stdout, __VA_ARGS__)
#else
#define LOG_INFO(...)
#endif

#ifdef NDEBUG
#define LOG_DEBUG(...) \
log_f(__FILE__, __func__, __LINE__, "DEBUG", LOGGER_DEBUG_COLOR, stdout, __VA_ARGS__)
#else
#define LOG_DEBUG(...)
#endif

#define LOGGER_CLEAR_COLOR "\x1B[0m"
#define LOGGER_ERROR_COLOR "\x1B[31m"
#define LOGGER_WARNING_COLOR "\x1B[33m"
#define LOGGER_INFO_COLOR "\x1B[35m"
#define LOGGER_DEBUG_COLOR "\x1B[36m"

void log_f(const char *file, const char *func, int line, const char *type, 
           const char *color, FILE *filePtr, const char *format, ...) {
    va_list ap;
    va_start(ap, format);

    fprintf(filePtr, "[%s%s%s][%s:%d in %s]: ", color, type, LOGGER_CLEAR_COLOR, file, line, func);
    vfprintf(filePtr, format, ap);
    fprintf(filePtr, "\n");

    va_end(ap);
}