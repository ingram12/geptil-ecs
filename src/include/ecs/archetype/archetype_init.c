#include "archetype_init.h"
#include "../../memory/arena.h"

void geptil_grow_archetype(Geptil_Context *ctx, Geptil_Ecs *ecs) {
    ecs->archetypes = (Geptil_Archetype *)geptil_arena_realloc(
        &ctx->arena,
        ecs->archetypes,
        sizeof(Geptil_Archetype) * ecs->archetype_capacity,
        sizeof(Geptil_Archetype) * ecs->archetype_capacity * 2
    );
    
    ecs->component_masks = (Geptil_ComponentMask *)geptil_arena_realloc(
        &ctx->arena,
        ecs->component_masks,
        sizeof(Geptil_ComponentMask) * ecs->archetype_capacity,
        sizeof(Geptil_ComponentMask) * ecs->archetype_capacity * 2
    );

    ecs->archetype_capacity *= 2;
}

u32 geptil_archetype_init(Geptil_Context *ctx, Geptil_ComponentMask component_mask) {
    Geptil_Arena* arena = &ctx->arena;
    Geptil_Ecs* ecs = &ctx->ecs;

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
        geptil_grow_archetype(ctx, ecs);
    }

    // Add a new archetype
    size_t index = ecs->archetype_count;
    ecs->component_masks[index] = component_mask;

    Geptil_Archetype *arch = &ecs->archetypes[index];
    arch->entity_count = 0;
    arch->entity_capacity = 256;
    arch->entities = (u32 *)geptil_arena_alloc(arena, sizeof(u32) * arch->entity_capacity);

    geptil_components_storage_init(arena, arch, ecs->component_masks[index], arch->entity_capacity);

    ecs->archetype_count++;

    return index;
}
