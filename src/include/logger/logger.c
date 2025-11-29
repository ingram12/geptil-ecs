#include "logger.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

static LogLevel g_log_level = LOG_LEVEL_DEBUG;
static FILE *g_log_output = NULL;

static const char *level_name(LogLevel lvl)
{
    switch (lvl) {
        case LOG_LEVEL_DEBUG: return "DEBUG";
        case LOG_LEVEL_INFO:  return "INFO";
        case LOG_LEVEL_WARN:  return "WARN";
        case LOG_LEVEL_ERROR: return "ERROR";
        case LOG_LEVEL_FATAL: return "FATAL";
        default: return "LOG";
    }
}

#if LOGGER_DEBUG
#define COLOR_DEBUG "\033[36m"  // cyan text
#define COLOR_INFO  "\033[32m"  // green text
#define COLOR_WARN  "\033[33m"  // yellow text
#define COLOR_ERROR "\033[31m"  // red text
#define COLOR_FATAL "\033[31m"  // red text (не фон)
#define COLOR_RESET "\033[0m"
#else
#define COLOR_DEBUG ""
#define COLOR_INFO  ""
#define COLOR_WARN  ""
#define COLOR_ERROR ""
#define COLOR_FATAL ""
#define COLOR_RESET ""
#endif

static const char *level_color(LogLevel lvl)
{
    switch (lvl) {
        case LOG_LEVEL_DEBUG: return COLOR_DEBUG;
        case LOG_LEVEL_INFO:  return COLOR_INFO;
        case LOG_LEVEL_WARN:  return COLOR_WARN;
        case LOG_LEVEL_ERROR: return COLOR_ERROR;
        case LOG_LEVEL_FATAL: return COLOR_FATAL;
        default: return "";
    }
}

void logger_init(LogLevel level, FILE *output)
{
    g_log_level = level;
    g_log_output = output ? output : stderr;
}

void logger_set_level(LogLevel level)
{
    g_log_level = level;
}

void logger_log(
    LogLevel level,
    const char *file,
    int line,
    const char *func,
    const char *fmt,
    ...
) {
    FILE *out;
    time_t now;
    struct tm *tm_info;
    char ts[32];
    va_list args;

    if (level < g_log_level)
        return;

    out = g_log_output ? g_log_output : stderr;

    now = time(NULL);
    tm_info = localtime(&now);
    strftime(ts, sizeof(ts), "%H:%M:%S", tm_info);

#if LOGGER_DEBUG
    // Цвет только на уровень
    fprintf(
        out,
        "[%s%s%s] %s %s:%d %s(): ",
        level_color(level),  // цвет открывается
        level_name(level),   // текст уровня
        COLOR_RESET,         // цвет закрывается
        ts,
        file,
        line,
        func
    );
#else
    fprintf(
        out,
        "[%s] %s: ",
        level_name(level),
        ts
    );
#endif

    va_start(args, fmt);
    vfprintf(out, fmt, args);
    va_end(args);

    fprintf(out, "\n");
    fflush(out);

    if (level == LOG_LEVEL_FATAL) {
#if LOGGER_DEBUG
        abort();
#else
        exit(EXIT_FAILURE);
#endif
    }
}
