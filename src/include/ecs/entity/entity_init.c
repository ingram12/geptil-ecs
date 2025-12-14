#include "entity_init.h"


void geptil_grow_entity(Geptil_Arena *arena, Geptil_Ecs *ecs) {
    ecs->entities = (Geptil_Entity *)geptil_arena_realloc(
        arena,
        ecs->entities,
        sizeof(Geptil_Entity) * ecs->entity_capacity,
        sizeof(Geptil_Entity) * ecs->entity_capacity * 2
    );

    ecs->entity_capacity *= 2;
}

// Initialize an entity in the specified archetype.
// archetype_id - Must be a valid archetype ID. The archetype is not checked for validity.
// Returns the ID of the created entity.
Geptil_EntityId geptil_entity_init(Geptil_Context *ctx, u32 archetype_id, u32 flags) {
    Geptil_Ecs* ecs = &ctx->ecs;
    Geptil_Archetype* arch = &ecs->archetypes[archetype_id];

    if (ecs->entity_count >= ecs->entity_capacity) {
        geptil_grow_entity(&ctx->arena, ecs);
    }
    
    if (arch->entity_count >= arch->entity_capacity) {
        geptil_archetype_grow_capacity(&ctx->arena, arch);
    }

    u32 entity_index = arch->entity_count;
    arch->entities[entity_index] = ecs->entity_count;
    arch->entity_count++;

    Geptil_Entity* entity = &ecs->entities[ecs->entity_count];

    entity->generation = 0;
    entity->flags = flags;
    entity->archetype_index = archetype_id;
    entity->archetype_entity_index = entity_index;

    return (Geptil_EntityId) {
        .index = ecs->entity_count++,
        .generation = 0
    };

}
