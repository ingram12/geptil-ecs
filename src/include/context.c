#include "context.h"
#include <stdint.h>
#include <stdlib.h>

static void create_ecs(Context* context, uint16_t max_components_count);

Context* create_context(uint16_t max_components_count) {
    Arena arena;
    arena_init(&arena, 1024 * 1024);
    if (!arena.buffer) return NULL;

    Context* context = (Context*) arena_alloc(&arena, sizeof(Context));
    context->arena = arena;

    create_ecs(context, max_components_count);

    return context;
}

static void create_ecs(Context* context, uint16_t max_components_count) {
    uint16_t component_masks_size = max_components_count / 64 + (max_components_count % 64 != 0 ? 1 : 0);

    context->ecs = (Ecs*) arena_alloc(&context->arena, sizeof(Ecs));

    context->ecs->entities = (Entity*) arena_alloc(&context->arena, sizeof(Entity) * 256);
    context->ecs->entity_count = 0;
    context->ecs->entity_capacity = 256;

    context->ecs->max_components_count = max_components_count;
    context->ecs->component_masks_size = component_masks_size;
    context->ecs->component_types = (ComponentType*) arena_alloc(&context->arena, sizeof(ComponentType) * max_components_count);
    context->ecs->component_type_count = 0;

    context->ecs->archetypes.component_masks = (uint64_t*) arena_alloc(&context->arena, sizeof(uint64_t) * component_masks_size);

    context->ecs->archetypes.archetypes = (Archetype*) arena_alloc(&context->arena, sizeof(Archetype) * 64);
    context->ecs->archetypes.archetype_count = 0;
    context->ecs->archetypes.archetype_capacity = 64;

    context->ecs->archetypes.query_masks = (uint64_t*) arena_alloc(&context->arena, sizeof(uint64_t) * 64);
    context->ecs->archetypes.query_archetype_indices = (QueryArchetypeIndices*) arena_alloc(&context->arena, sizeof(QueryArchetypeIndices) * 64);
    context->ecs->archetypes.query_count = 0;
    context->ecs->archetypes.query_capacity = 64;
}

void destroy_context(Context* context) {
    if (!context) return;
    arena_destroy(&context->arena);
}
