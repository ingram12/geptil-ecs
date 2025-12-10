#pragma once

#include "../memory/arena.h"
#include "component/components.gen.h"
#include <stddef.h>
#include <stdint.h>

typedef struct QueryArchetypeIndices {
    uint32_t *indices;
    uint32_t count;
} QueryArchetypeIndices;

typedef struct Archetypes {
    ComponentMask *component_masks; // индекс масок и архетипа совпадает
    Archetype *archetypes; // индекс масок и архетипа совпадает
    uint32_t archetype_count;
    uint32_t archetype_capacity;

    ComponentMask *query_masks; // индекс маски и запроса совпадает
    QueryArchetypeIndices *query_archetype_indices; // индекс маски и запроса совпадает
    uint32_t query_count;
    uint32_t query_capacity;
} Archetypes;

typedef struct Entity {
    uint32_t id;
    uint32_t archetype_index;
    uint32_t component_index;
    uint8_t alive;
} Entity;

typedef struct Ecs {
    Entity *entities;
    uint32_t entity_count;
    uint32_t entity_capacity;
    Archetypes archetypes;
} Ecs;

Ecs *init_ecs(Arena *arena, Ecs *ecs);

ComponentMask build_component_masks(const uint32_t *components, const size_t count);
