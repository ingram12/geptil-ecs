#include "context.h"
#include <stdint.h>
#include <stdlib.h>

Context *create_context(uint16_t max_components_count)
{
    Arena arena;
    arena_init(&arena, 1024 * 1024);

    Context *context = (Context *)arena_alloc(&arena, sizeof(Context));
    context->arena = arena;

    context->ecs = init_ecs(&context->arena, max_components_count);

    return context;
}

void destroy_context(Context *context)
{
    if (!context)
        return;
    arena_destroy(&context->arena);
}
