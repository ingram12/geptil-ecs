#include "../memory/arena.h"
#include "ecs.h"
#include <stdint.h>
#include <stdlib.h>

Ecs *init_ecs(Arena *arena, Ecs *ecs, uint16_t max_components_count)
{
    uint16_t component_masks_size = max_components_count / 64 + (max_components_count % 64 != 0 ? 1 : 0);

    ecs->entities = (Entity *)arena_alloc(arena, sizeof(Entity) * 256);
    ecs->entity_count = 0;
    ecs->entity_capacity = 256;

    ecs->max_components_count = max_components_count;
    ecs->component_masks_size = component_masks_size;

    ecs->archetypes.component_masks = (uint64_t *)arena_alloc(arena, sizeof(uint64_t) * component_masks_size);

    ecs->archetypes.archetypes = (Archetype *)arena_alloc(arena, sizeof(Archetype) * 64);
    ecs->archetypes.archetype_count = 0;
    ecs->archetypes.archetype_capacity = 64;

    ecs->archetypes.query_masks = (uint64_t *)arena_alloc(arena, sizeof(uint64_t) * 64);
    ecs->archetypes.query_archetype_indices = (QueryArchetypeIndices *)arena_alloc(arena, sizeof(QueryArchetypeIndices) * 64);
    ecs->archetypes.query_count = 0;
    ecs->archetypes.query_capacity = 64;

    return ecs;
}
