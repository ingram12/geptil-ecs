#include "query.h"

Entity* get_entity_by_id(const Context *ctx, const EntityId entity_id) {
    Entity* entity = &ctx->ecs.entities[entity_id.index];
    if (entity->generation != entity_id.generation) {
        return NULL;
    }

    return entity;
}
