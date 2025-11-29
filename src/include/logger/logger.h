#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>
#include <stdio.h>

#ifndef NDEBUG
#define LOGGER_DEBUG 1
#else
#define LOGGER_RELEASE 1
#endif

typedef enum {
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO = 1,
    LOG_LEVEL_WARN = 2,
    LOG_LEVEL_ERROR = 3,
    LOG_LEVEL_FATAL = 4
} LogLevel;

void logger_init(LogLevel level, FILE *output);
void logger_set_level(LogLevel level);

void logger_log(
    LogLevel level,
    const char *file,
    int line,
    const char *func,
    const char *fmt,
    ...
);

#if LOGGER_DEBUG
#define LOG_DEBUG(...) logger_log(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_INFO(...) logger_log(LOG_LEVEL_INFO, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_WARN(...) logger_log(LOG_LEVEL_WARN, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_ERROR(...) logger_log(LOG_LEVEL_ERROR, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define LOG_FATAL(...) logger_log(LOG_LEVEL_FATAL, __FILE__, __LINE__, __func__, __VA_ARGS__)
#else
#define LOG_DEBUG(...) ((void)0)
#define LOG_INFO(...) logger_log(LOG_LEVEL_INFO, 0, 0, 0, __VA_ARGS__)
#define LOG_WARN(...) logger_log(LOG_LEVEL_WARN, 0, 0, 0, __VA_ARGS__)
#define LOG_ERROR(...) logger_log(LOG_LEVEL_ERROR, 0, 0, 0, __VA_ARGS__)
#define LOG_FATAL(...) logger_log(LOG_LEVEL_FATAL, 0, 0, 0, __VA_ARGS__)
#endif

#endif /* LOGGER_H */
