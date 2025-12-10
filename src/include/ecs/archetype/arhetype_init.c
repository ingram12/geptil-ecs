#include "arhetype_init.h"
#include "../../logger/logger.h"
#include "../../memory/arena.h"
#include <string.h>

uint32_t archetype_init(Context *ctx, uint64_t component_masks[COMPONENT_MASK_COUNT]) {
    Arena* arena = &ctx->arena;
    Ecs* ecs = &ctx->ecs;

    // Проверить, существует ли уже архетип с такой маской
    for (size_t i = 0; i < ecs->archetypes.archetype_count; ++i) {
        for (size_t j = 0; j < COMPONENT_MASK_COUNT; ++j) {
            if (ecs->archetypes.component_masks[i][j] != component_masks[j]) {
                break;
            }
            if (j == COMPONENT_MASK_COUNT - 1) {
                return i;
            }
        }
    }

    // Если превысили capacity, ошибка
    if (ecs->archetypes.archetype_count >= ecs->archetypes.archetype_capacity) {
        LOG_FATAL("Exceeded maximum number of archetypes");
        return 0;
    }
    // Добавить новый архетип
    size_t index = ecs->archetypes.archetype_count;
    memcpy(ecs->archetypes.component_masks[index], component_masks, sizeof(uint64_t) * COMPONENT_MASK_COUNT);

    Archetype *arch = &ecs->archetypes.archetypes[index];
    arch->entity_count = 0;
    arch->entity_capacity = 64;
    arch->entities = (uint32_t *)arena_alloc(arena, sizeof(uint32_t) * arch->entity_capacity);

    components_storage_init(arena, arch, ecs->archetypes.component_masks[index], arch->entity_capacity);

    ecs->archetypes.archetype_count++;

    return index;
}
