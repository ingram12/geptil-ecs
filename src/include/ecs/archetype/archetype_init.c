#include "archetype_init.h"
#include "../../memory/arena.h"

void grow_archetype(Context *ctx, Ecs *ecs) {
    ecs->archetypes = (Archetype *)arena_realloc(
        &ctx->arena,
        ecs->archetypes,
        sizeof(Archetype) * ecs->archetype_capacity,
        sizeof(Archetype) * ecs->archetype_capacity * 2
    );
    
    ecs->component_masks = (ComponentMask *)arena_realloc(
        &ctx->arena,
        ecs->component_masks,
        sizeof(ComponentMask) * ecs->archetype_capacity,
        sizeof(ComponentMask) * ecs->archetype_capacity * 2
    );

    ecs->archetype_capacity *= 2;
}

u32 archetype_init(Context *ctx, ComponentMask component_mask) {
    Arena* arena = &ctx->arena;
    Ecs* ecs = &ctx->ecs;

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

    if (ecs->archetype_count >= ecs->archetype_capacity) {
        grow_archetype(ctx, ecs);
    }

    // Add a new archetype
    size_t index = ecs->archetype_count;
    ecs->component_masks[index] = component_mask;

    Archetype *arch = &ecs->archetypes[index];
    arch->entity_count = 0;
    arch->entity_capacity = 256;
    arch->entities = (u32 *)arena_alloc(arena, sizeof(u32) * arch->entity_capacity);

    components_storage_init(arena, arch, ecs->component_masks[index], arch->entity_capacity);

    ecs->archetype_count++;

    return index;
}
