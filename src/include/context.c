#include "context.h"
#include "logger/logger.h"
#include <stdint.h>
#include <stdlib.h>

void init_context(Context *context)
{
    if (!context) {
        LOG_FATAL("Failed to allocate memory for Context");
    };

    arena_init(&context->arena, 1024 * 1024);
    init_ecs(&context->arena, &context->ecs);
}

void destroy_context(Context *context)
{
    if (!context)
        return;
    arena_destroy(&context->arena);
}
