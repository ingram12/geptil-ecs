#pragma once

#include "../memory/arena.h"
#include "component/components.gen.h"

typedef struct Geptil_QueryArchetypeIndices {
    u32 *indices;
    u32 count;
    u32 capacity;
} Geptil_QueryArchetypeIndices;

typedef struct Geptil_Entity {
    u32 generation;
    u32 flags;
    u32 archetype_index;
    u32 archetype_entity_index;
} Geptil_Entity;

typedef struct Geptil_EntityId {
    u32 index;
    u32 generation;
} Geptil_EntityId;

typedef struct Geptil_Ecs {
    Geptil_Entity *entities;
    u32 entity_count;
    u32 entity_capacity;
    
    Geptil_ComponentMask *component_masks; // component_masks and archetypes share the same index
    Geptil_Archetype *archetypes; // component_masks and archetypes share the same index
    u32 archetype_count;
    u32 archetype_capacity;

    Geptil_ComponentMask *query_masks; // query_masks and query_archetype_indices share the same index
    Geptil_QueryArchetypeIndices *query_archetype_indices; // query_masks and query_archetype_indices share the same index
    u32 query_count;
    u32 query_capacity;
} Geptil_Ecs;

Geptil_Ecs *geptil_init_ecs(Geptil_Arena *arena, Geptil_Ecs *ecs);

Geptil_ComponentMask geptil_build_component_mask(const ComponentIndex *components, const size_t count);

Geptil_Entity* geptil_get_entity_by_id(const Geptil_Ecs *ecs, const Geptil_EntityId entity_id);
Geptil_Archetype* geptil_get_archetype_by_id(const Geptil_Ecs *ecs, const u32 archetype_id);
Geptil_Archetype* geptil_get_archetype_by_component_mask(const Geptil_Ecs *ecs, const Geptil_ComponentMask component_mask);
