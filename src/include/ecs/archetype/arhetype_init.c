#include "arhetype_init.h"
#include "../../logger/logger.h"
#include "../../memory/arena.h"
#include <string.h>

uint32_t archetype_init(Context *ctx, const ComponentIndex *components, size_t component_count) {
    Arena* arena = &ctx->arena;
    Ecs* ecs = &ctx->ecs;

    ComponentMask component_mask = build_component_masks(components, component_count);

    // Check if an archetype with this mask already exists
    for (size_t i = 0; i < ecs->archetype_count; ++i) {
        for (size_t j = 0; j < COMPONENT_MASK_COUNT; ++j) {
            if (ecs->component_masks[i].mask[j] != component_mask.mask[j]) {
                break;
            }
            if (j == COMPONENT_MASK_COUNT - 1) {
                return i;
            }
        }
    }

    // If archetype capacity is exceeded, log fatal error
    if (ecs->archetype_count >= ecs->archetype_capacity) {
        LOG_FATAL("Exceeded maximum number of archetypes");
        return 0;
    }
    // Add a new archetype
    size_t index = ecs->archetype_count;
    ecs->component_masks[index] = component_mask;

    Archetype *arch = &ecs->archetypes[index];
    arch->entity_count = 0;
    arch->entity_capacity = 256;
    arch->entities = (uint32_t *)arena_alloc(arena, sizeof(uint32_t) * arch->entity_capacity);

    components_storage_init(arena, arch, ecs->component_masks[index], arch->entity_capacity);

    ecs->archetype_count++;

    return index;
}
