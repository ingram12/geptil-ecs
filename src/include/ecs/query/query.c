#include "query.h"

void geptil_grow_query_indices(Geptil_Arena *arena, Geptil_QueryArchetypeIndices *query_indices) {   
    query_indices->indices = (u32 *)geptil_arena_realloc(
        arena,
        query_indices->indices,
        sizeof(u32) * query_indices->capacity,
        sizeof(u32) * (query_indices->capacity * 2)
    );
    query_indices->capacity *= 2;    
}

void geptil_grow_query(Geptil_Arena *arena, Geptil_Ecs *ecs) {
    ecs->query_masks = (Geptil_ComponentMask *)geptil_arena_realloc(
        arena, 
        ecs->query_masks, 
        sizeof(Geptil_ComponentMask) * ecs->query_capacity,
        sizeof(Geptil_ComponentMask) * (ecs->query_capacity * 2)
    );

    ecs->query_archetype_indices = (Geptil_QueryArchetypeIndices *)geptil_arena_realloc(
        arena,
        ecs->query_archetype_indices,
        sizeof(Geptil_QueryArchetypeIndices) * ecs->query_capacity,
        sizeof(Geptil_QueryArchetypeIndices) * (ecs->query_capacity * 2)
    );

    ecs->query_capacity *= 2;
}

u32 geptil_init_query(Geptil_Arena *arena, Geptil_Ecs *ecs, const Geptil_ComponentMask component_mask) {
    for (u32 i = 0; i < ecs->query_count; ++i) {
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
        geptil_grow_query(arena, ecs);
    }

    u32 query_index = ecs->query_count++;
    ecs->query_masks[query_index] = component_mask;

    // Find matching archetypes for the new query
    Geptil_QueryArchetypeIndices *query_indices = &ecs->query_archetype_indices[query_index];
    query_indices->count = 0;
    query_indices->capacity = 64;
    query_indices->indices = geptil_arena_alloc(arena, sizeof(u32) * query_indices->capacity);

    for (u32 i = 0; i < ecs->archetype_count; ++i) {
        char matches = 1;
        for (size_t j = 0; j < COMPONENT_MASK_COUNT; ++j) {
            if ((ecs->component_masks[i].mask[j] & component_mask.mask[j]) != component_mask.mask[j]) {
                matches = 0;
                break;
            }
        }
        if (matches) {
            if (query_indices->count >= query_indices->capacity) {
                geptil_grow_query_indices(arena, query_indices);
            }

                query_indices->indices[query_indices->count++] = i;
        }
    }

    return query_index;
}

void geptil_rematch_all_queries(Geptil_Arena *arena, Geptil_Ecs *ecs) {
    for (u32 q = 0; q < ecs->query_count; ++q) {
        Geptil_ComponentMask component_mask = ecs->query_masks[q];
        Geptil_QueryArchetypeIndices *query_indices = &ecs->query_archetype_indices[q];

        // Clear existing indices
        query_indices->count = 0;

        for (u32 i = 0; i < ecs->archetype_count; ++i) {
            char matches = 1;
            for (size_t j = 0; j < COMPONENT_MASK_COUNT; ++j) {
                if ((ecs->component_masks[i].mask[j] & component_mask.mask[j]) != component_mask.mask[j]) {
                    matches = 0;
                    break;
                }
            }
            if (matches) {
                if (query_indices->count >= query_indices->capacity) {
                    geptil_grow_query_indices(arena, query_indices);
                }

                query_indices->indices[query_indices->count++] = i;
            }
        }
    }
}
