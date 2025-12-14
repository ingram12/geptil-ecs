#include "ecs.h"

Geptil_Entity* geptil_get_entity_by_id(const Geptil_Ecs *ecs, const Geptil_EntityId entity_id) {
    Geptil_Entity* entity = &ecs->entities[entity_id.index];
    if (entity->generation != entity_id.generation) {
        return NULL;
    }

    return entity;
}

Geptil_Archetype* geptil_get_archetype_by_id(const Geptil_Ecs *ecs, const u32 archetype_id) {
    if (archetype_id >= ecs->archetype_count) {
        return NULL;
    }

    return &ecs->archetypes[archetype_id];
}

Geptil_Archetype* geptil_get_archetype_by_component_mask(const Geptil_Ecs *ecs, const Geptil_ComponentMask component_mask) {
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
