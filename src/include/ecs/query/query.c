#include "query.h"

void grow_query_indices(Arena *arena, QueryArchetypeIndices *query_indices) {   
    query_indices->indices = arena_realloc(
        arena,
        query_indices->indices,
        sizeof(uint32_t) * query_indices->capacity,
        sizeof(uint32_t) * (query_indices->capacity * 2)
    );
    query_indices->capacity *= 2;    
}

void grow_query(Arena *arena, Ecs *ecs) {
    ecs->query_masks = arena_realloc(
        arena, 
        ecs->query_masks, 
        sizeof(ComponentMask) * ecs->query_capacity,
        sizeof(ComponentMask) * (ecs->query_capacity * 2)
    );

    ecs->query_archetype_indices = arena_realloc(
        arena,
        ecs->query_archetype_indices,
        sizeof(QueryArchetypeIndices) * ecs->query_capacity,
        sizeof(QueryArchetypeIndices) * (ecs->query_capacity * 2)
    );

    ecs->query_capacity *= 2;
}

uint32_t init_query(Arena *arena, Ecs *ecs, const ComponentMask component_mask) {
    for (uint32_t i = 0; i < ecs->query_count; ++i) {
        char match = 1;
        for (size_t j = 0; j < COMPONENT_MASK_COUNT; ++j) {
            if (ecs->query_masks[i].mask[j] != component_mask.mask[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            return i; // Return existing query index
        }
    }

    if (ecs->query_count >= ecs->query_capacity) {
        grow_query(arena, ecs);
    }

    uint32_t query_index = ecs->query_count++;
    ecs->query_masks[query_index] = component_mask;

    // Find matching archetypes for the new query
    QueryArchetypeIndices *query_indices = &ecs->query_archetype_indices[query_index];
    query_indices->count = 0;
    query_indices->capacity = 64;
    query_indices->indices = arena_alloc(arena, sizeof(uint32_t) * query_indices->capacity);

    for (uint32_t i = 0; i < ecs->archetype_count; ++i) {
        char matches = 1;
        for (size_t j = 0; j < COMPONENT_MASK_COUNT; ++j) {
            if ((ecs->component_masks[i].mask[j] & component_mask.mask[j]) != component_mask.mask[j]) {
                matches = 0;
                break;
            }
        }
        if (matches) {
            if (query_indices->count >= query_indices->capacity) {
                grow_query_indices(arena, query_indices);
            }

            query_indices->indices[query_indices->count++] = i;
        }
    }

    return query_index;
}

void rematch_all_queries(Ecs *ecs, Arena *arena) {
    for (uint32_t q = 0; q < ecs->query_count; ++q) {
        ComponentMask component_mask = ecs->query_masks[q];
        QueryArchetypeIndices *query_indices = &ecs->query_archetype_indices[q];

        // Clear existing indices
        query_indices->count = 0;

        for (uint32_t i = 0; i < ecs->archetype_count; ++i) {
            char matches = 1;
            for (size_t j = 0; j < COMPONENT_MASK_COUNT; ++j) {
                if ((ecs->component_masks[i].mask[j] & component_mask.mask[j]) != component_mask.mask[j]) {
                    matches = 0;
                    break;
                }
            }
            if (matches) {
                if (query_indices->count >= query_indices->capacity) {
                    grow_query_indices(arena, query_indices);
                }

                query_indices->indices[query_indices->count++] = i;
            }
        }
    }
}
