#include "../memory/arena.h"
#include "ecs.h"

Geptil_Ecs *geptil_init_ecs(Geptil_Arena *arena, Geptil_Ecs *ecs)
{
    ecs->entities = (Geptil_Entity *)geptil_arena_alloc(arena, sizeof(Geptil_Entity) * 1024);
    ecs->entity_count = 0;
    ecs->entity_capacity = 1024;

    ecs->component_masks = geptil_arena_alloc(arena, sizeof(u64[256][COMPONENT_MASK_COUNT]));

    ecs->archetypes = (Geptil_Archetype *)geptil_arena_alloc(arena, sizeof(Geptil_Archetype) * 256);
    ecs->archetype_count = 0;
    ecs->archetype_capacity = 256;

    ecs->query_masks = geptil_arena_alloc(arena, sizeof(u64[256][COMPONENT_MASK_COUNT]));
    ecs->query_archetype_indices = (Geptil_QueryArchetypeIndices *)geptil_arena_alloc(arena, sizeof(Geptil_QueryArchetypeIndices) * 256);
    ecs->query_count = 0;
    ecs->query_capacity = 256;
    
    return ecs;
}
