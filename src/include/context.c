#include "context.h"
#include "logger/logger.h"

void geptil_init_context(Geptil_Context *context)
{
    if (!context) {
        LOG_FATAL("Context pointer is NULL");
    };

    geptil_arena_init(&context->arena, 1024 * 1024 * 10); // 10 MB
    geptil_init_ecs(&context->arena, &context->ecs);
}

void geptil_destroy_context(Geptil_Context *context)
{
    if (!context)
        return;
    geptil_arena_destroy(&context->arena);
}
