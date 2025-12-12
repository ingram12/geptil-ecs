#include "ecs.h"

Entity* get_entity_by_id(const Ecs *ecs, const EntityId entity_id) {
    Entity* entity = &ecs->entities[entity_id.index];
    if (entity->generation != entity_id.generation) {
        return NULL;
    }

    return entity;
}

Archetype* get_archetype_by_id(const Ecs *ecs, const uint32_t archetype_id) {
    if (archetype_id >= ecs->archetype_count) {
        return NULL;
    }

    return &ecs->archetypes[archetype_id];
}

Archetype* get_archetype_by_component_mask(const Ecs *ecs, const ComponentMask component_mask) {
    for (size_t i = 0; i < ecs->archetype_count; ++i) {
        for (size_t j = 0; j < COMPONENT_MASK_COUNT; ++j) {
            if (ecs->component_masks[i].mask[j] != component_mask.mask[j]) {
                break;
            }
            if (j == COMPONENT_MASK_COUNT - 1) {
                return &ecs->archetypes[i];
            }
        }
    }

    return NULL;
}