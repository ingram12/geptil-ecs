#include "entity_init.h"

uint32_t entity_init(Context *ctx, uint32_t archetype_id) {
    Ecs* ecs = &ctx->ecs;
    Archetype* arch = &ecs->archetypes.archetypes[archetype_id];
    
    if (arch->entity_count >= arch->entity_capacity) {
        // TODO: Реализация расширения емкости архетипа
    }

    uint32_t entity_index = arch->entity_count;
    arch->entity_count++;

    if (arch->entity_count >= arch->entity_capacity) {
        // TODO: Реализация расширения емкости архетипа
    }

    Entity* entity = &ecs->entities[ecs->entity_count];

    entity->id = ecs->entity_count;
    entity->archetype_index = archetype_id;
    entity->component_index = entity_index;
    entity->alive = 1;

    ecs->entity_count++;

    return entity->id;
}