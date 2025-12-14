#include "../memory/arena.h"
#include "ecs.h"

Ecs *init_ecs(Arena *arena, Ecs *ecs)
{
    ecs->entities = (Entity *)arena_alloc(arena, sizeof(Entity) * 1024);
    ecs->entity_count = 0;
    ecs->entity_capacity = 1024;

    ecs->component_masks = arena_alloc(arena, sizeof(u64[256][COMPONENT_MASK_COUNT]));

    ecs->archetypes = (Archetype *)arena_alloc(arena, sizeof(Archetype) * 256);
    ecs->archetype_count = 0;
    ecs->archetype_capacity = 256;

    ecs->query_masks = arena_alloc(arena, sizeof(u64[256][COMPONENT_MASK_COUNT]));
    ecs->query_archetype_indices = (QueryArchetypeIndices *)arena_alloc(arena, sizeof(QueryArchetypeIndices) * 256);
    ecs->query_count = 0;
    ecs->query_capacity = 256;
    
    return ecs;
}
