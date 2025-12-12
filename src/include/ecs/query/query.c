#include "query.h"
#include "../../logger/logger.h"

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
        // TODO: Resize if needed!!!
        LOG_FATAL("Exceeded maximum number of queries");
    }

    uint32_t query_index = ecs->query_count++;
    ecs->query_masks[query_index] = component_mask;

    // Find matching archetypes for the new query
    QueryArchetypeIndices *query_indices = &ecs->query_archetype_indices[query_index];
    query_indices->indices = arena_alloc(arena, sizeof(uint32_t) * 64);
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
            // Add archetype index to the query's archetype indices
            // TODO: Resize if needed!!!
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
                // Add archetype index to the query's archetype indices
                // TODO: Resize if needed!!!
                query_indices->indices[query_indices->count++] = i;
            }
        }
    }
}