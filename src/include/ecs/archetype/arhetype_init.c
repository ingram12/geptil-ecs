#include "arhetype_init.h"
#include "../../logger/logger.h"
#include "../../memory/arena.h"

Archetype *archetype_init(Context *ctx, uint64_t component_mask) {
    Ecs *ecs = ctx->ecs;
    Arena arena = ctx->arena;

    // Проверить, существует ли уже архетип с такой маской
    for (size_t i = 0; i < ecs->archetypes.archetype_count; ++i) {
        if (ecs->archetypes.component_masks[i] == component_mask) {
            return &ecs->archetypes.archetypes[i];
        }
    }

    // Если превысили capacity, ошибка
    if (ecs->archetypes.archetype_count >= ecs->archetypes.archetype_capacity) {
        LOG_FATAL("Exceeded maximum number of archetypes");
        return NULL;
    }

    // Добавить новый архетип
    size_t index = ecs->archetypes.archetype_count;
    ecs->archetypes.component_masks[index] = component_mask;

    Archetype *arch = &ecs->archetypes.archetypes[index];
    arch->entity_count = 0;
    arch->entity_capacity = 64;
    arch->entities = (uint32_t *)arena_alloc(&arena, sizeof(uint32_t) * arch->entity_capacity);
    arch->component_arrays = (void **)arena_alloc(&arena, sizeof(void *) * ecs->max_components_count);

    //TODO: Получить по маске компоненты и инициализировать массивы компонентов

    for (uint16_t i = 0; i < ecs->max_components_count; ++i) {
        if (component_mask & (1ULL << i)) {
            ComponentType *ct = &ecs->component_types[i];
            arch->component_arrays[i] = arena_alloc(&arena, ct->size * arch->entity_capacity);
        } else {
            arch->component_arrays[i] = NULL;
        }
    }

    ecs->archetypes.archetype_count++;

    return arch;
}
