#include "move.h"

void geptil_system_move(Context *ctx) {
    Ecs *ecs = &ctx->ecs;

    u32 query_id = 0;

    u32 arch_count = ecs->query_archetype_indices[query_id].count;
    u32 *indices = ecs->query_archetype_indices[query_id].indices;

    for (u32 i = 0; i < arch_count; ++i) {
        u32 entity_count = ecs->archetypes[indices[i]].entity_count;
        Position *positions = ecs->archetypes[indices[i]].positions;

        for (u32 j = 0; j < entity_count; ++j) {
            Position *pos = &positions[j];

            pos->x += j + 5.0;
            pos->y += 1.0;
            pos->z += 1.0;
        }
    }
}
