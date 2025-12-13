#include "entity_init.h"


void grow_entity(Arena *arena, Ecs *ecs) {
    ecs->entities = (Entity *)arena_realloc(
        arena,
        ecs->entities,
        sizeof(Entity) * ecs->entity_capacity,
        sizeof(Entity) * ecs->entity_capacity * 2
    );

    ecs->entity_capacity *= 2;
}

// Инициализация сущности в указанном архетипе.
// archetype_id - Должен быть валидным ID архетипа. Архетип не проверяется на валидность.
// Возвращает ID созданной сущности.
EntityId entity_init(Context *ctx, uint32_t archetype_id, uint32_t flags) {
    Ecs* ecs = &ctx->ecs;
    Archetype* arch = &ecs->archetypes[archetype_id];

    if (ecs->entity_count >= ecs->entity_capacity) {
        grow_entity(&ctx->arena, ecs);
    }
    
    if (arch->entity_count >= arch->entity_capacity) {
        grow_archtype_entity(&ctx->arena, arch);
    }

    uint32_t entity_index = arch->entity_count;
    arch->entities[entity_index] = ecs->entity_count;
    arch->entity_count++;

    Entity* entity = &ecs->entities[ecs->entity_count];

    entity->generation = 0;
    entity->flags = flags;
    entity->archetype_index = archetype_id;
    entity->archetype_entity_index = entity_index;

    return (EntityId) {
        .index = ecs->entity_count++,
        .generation = 0
    };

}
