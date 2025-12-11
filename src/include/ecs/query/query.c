#include "query.h"

Entity* get_entity_by_id(const Context *ctx, const EntityId entity_id) {
    Ecs* ecs = &ctx->ecs;

    Entity* entity = &ecs->entities[entity_id.index];
    if (entity->generation != entity_id.generation) {
        return NULL;
    }

    return entity;
}
