#include "entity_init.h"

// Инициализация сущности в указанном архетипе.
// archetype_id - Должен быть валидным ID архетипа. Архетип не проверяется на валидность.
// Возвращает ID созданной сущности.
uint32_t entity_init(Context *ctx, uint32_t archetype_id, uint32_t flags) {
    Ecs* ecs = &ctx->ecs;
    Archetype* arch = &ecs->archetypes.archetypes[archetype_id];
    
    if (arch->entity_count >= arch->entity_capacity) {
        // TODO: Реализация расширения емкости архетипа
    }

    if (ecs->entity_count >= ecs->entity_capacity) {
        // TODO: Реализация расширения емкости сущностей
    }

    uint32_t entity_index = arch->entity_count;
    arch->entities[entity_index] = ecs->entity_count;
    arch->entity_count++;

    Entity* entity = &ecs->entities[ecs->entity_count];

    entity->id = ecs->entity_count;
    entity->generation = 0;
    entity->flags = flags;
    entity->archetype_index = archetype_id;
    entity->archetype_entity_index = entity_index;

    ecs->entity_count++;

    return entity->id;
}
