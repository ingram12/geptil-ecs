#include "entity_init.h"


void geptil_grow_entity(Arena *arena, Ecs *ecs) {
    ecs->entities = (Entity *)geptil_arena_realloc(
        arena,
        ecs->entities,
        sizeof(Entity) * ecs->entity_capacity,
        sizeof(Entity) * ecs->entity_capacity * 2
    );

    ecs->entity_capacity *= 2;
}

// Initialize an entity in the specified archetype.
// archetype_id - Must be a valid archetype ID. The archetype is not checked for validity.
// Returns the ID of the created entity.
EntityId geptil_entity_init(Context *ctx, u32 archetype_id, u32 flags) {
    Ecs* ecs = &ctx->ecs;
    Archetype* arch = &ecs->archetypes[archetype_id];

    if (ecs->entity_count >= ecs->entity_capacity) {
        geptil_grow_entity(&ctx->arena, ecs);
    }
    
    if (arch->entity_count >= arch->entity_capacity) {
        geptil_archetype_grow_capacity(&ctx->arena, arch);
    }

    u32 entity_index = arch->entity_count;
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
