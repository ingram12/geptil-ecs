#include "../memory/arena.h"
#include "ecs.h"
#include <stdint.h>
#include <stdlib.h>

Ecs *init_ecs(Arena *arena, Ecs *ecs)
{
    ecs->entities = (Entity *)arena_alloc(arena, sizeof(Entity) * 1024);
    ecs->entity_count = 0;
    ecs->entity_capacity = 1024;

    ecs->archetypes.component_masks = arena_alloc(arena, sizeof(uint64_t[256][COMPONENT_MASK_COUNT]));

    ecs->archetypes.archetypes = (Archetype *)arena_alloc(arena, sizeof(Archetype) * 256);
    ecs->archetypes.archetype_count = 0;
    ecs->archetypes.archetype_capacity = 256;

    ecs->archetypes.query_masks = arena_alloc(arena, sizeof(uint64_t[256][COMPONENT_MASK_COUNT]));
    ecs->archetypes.query_archetype_indices = (QueryArchetypeIndices *)arena_alloc(arena, sizeof(QueryArchetypeIndices) * 256);
    ecs->archetypes.query_count = 0;
    ecs->archetypes.query_capacity = 256;
    
    return ecs;
}
