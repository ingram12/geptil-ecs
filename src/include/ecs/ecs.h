#pragma once

#include "../memory/arena.h"
#include "component/components.gen.h"

typedef struct QueryArchetypeIndices {
    u32 *indices;
    u32 count;
    u32 capacity;
} QueryArchetypeIndices;

typedef struct Entity {
    u32 generation;
    u32 flags;
    u32 archetype_index;
    u32 archetype_entity_index;
} Entity;

typedef struct EntityId {
    u32 index;
    u32 generation;
} EntityId;

typedef struct Ecs {
    Entity *entities;
    u32 entity_count;
    u32 entity_capacity;
    
    ComponentMask *component_masks; // component_masks and archetypes share the same index
    Archetype *archetypes; // component_masks and archetypes share the same index
    u32 archetype_count;
    u32 archetype_capacity;

    ComponentMask *query_masks; // query_masks and query_archetype_indices share the same index
    QueryArchetypeIndices *query_archetype_indices; // query_masks and query_archetype_indices share the same index
    u32 query_count;
    u32 query_capacity;
} Ecs;

Ecs *geptil_init_ecs(Arena *arena, Ecs *ecs);

ComponentMask geptil_build_component_mask(const ComponentIndex *components, const size_t count);

Entity* geptil_get_entity_by_id(const Ecs *ecs, const EntityId entity_id);
Archetype* geptil_get_archetype_by_id(const Ecs *ecs, const u32 archetype_id);
Archetype* geptil_get_archetype_by_component_mask(const Ecs *ecs, const ComponentMask component_mask);
