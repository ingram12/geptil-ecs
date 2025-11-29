#pragma once

#include "../memory/arena.h"
#include "component/component.h"
#include <stddef.h>
#include <stdint.h>

typedef struct Archetype
{
    uint32_t *entities;
    ComponentStorage storage; // хранилище значений массивов компонентов
    size_t entity_count;
    size_t entity_capacity;
} Archetype;

typedef struct QueryArchetypeIndices
{
    size_t *indices;
    size_t count;
} QueryArchetypeIndices;

typedef struct Archetypes
{
    uint64_t *component_masks; // первая маска hot остальные cold (если есть),
                               // кол-во масок определяется в component_masks_size
    Archetype *archetypes;     // индекс маски и архетипа совпадает
    size_t archetype_count;
    size_t archetype_capacity;

    uint64_t *query_masks; // индекс маски и запроса совпадает
    QueryArchetypeIndices *query_archetype_indices; // индекс маски и запроса совпадает
    size_t query_count;
    size_t query_capacity;
} Archetypes;

typedef struct Entity
{
    uint32_t id;
    uint32_t archetype_index;
    uint32_t component_index;
    uint8_t alive;
} Entity;

typedef struct Ecs
{
    Entity *entities;
    size_t entity_count;
    size_t entity_capacity;

    uint16_t max_components_count; // максимально возможное кол-во типов компонентов в проекте
    uint16_t component_masks_size; // количество масок компонентов в массиве component_masks архетипа

    Archetypes archetypes;
} Ecs;

Ecs *init_ecs(Arena *arena, Ecs *ecs, uint16_t max_components_count);
